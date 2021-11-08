#include "./qstm_util_variant.h"
#include "./qstm_util_date.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCborCommon>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QCborArray>
#include <QCborMap>
#include <QCborValue>
#include <QCborParserError>
#include <QFile>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<VariantUtilPvt*>(this->p)


#define set__value(v)\
if(v.isValid()) {p.vvm.clear();this->setValue(v);}

class VariantUtilPvt:public QObject{
public:
    VariantUtil*parent=nullptr;
    QVVM vvm;

    explicit VariantUtilPvt(VariantUtil*v):QObject(nullptr){
        this->parent=v;
    }
    virtual ~VariantUtilPvt(){
    }

    void clear(){
        vvm.clear();
        this->parent->setValue(QVariant());
    }

    QVariantHash toHash(const QVariant &v)const
    {
        QVariantHash map;
        if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash)
            map=v.toHash();
        else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
            map.clear();
        else if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            else if(!doc.isEmpty() || !doc.isNull()){
                map=doc.object().toVariantHash();
            }
        }
        return map;
    }

    QVariantMap toMap(const QVariant &v)const
    {
        QVariantMap map;
        if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash)
            map=v.toMap();
        else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
            map.clear();
        else if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            else if(!doc.isEmpty() || !doc.isNull()){
                map=doc.object().toVariantMap();
            }
        }
        return map;
    }

    static QByteArray toMd5(const QVariant &v)
    {
        //if(v.isValid()) vBase->setValue(v);
        auto vType=v.typeId();
        if(!v.isValid())
            return qbl_null;

        if(vType==QMetaType::QUuid){
            auto uuid=v.toUuid();
            auto suuid=uuid.toByteArray();
            auto md5=suuid.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"), qbl_null);
            if(md5.length()==32)
                return md5;
            else
                return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
        }

        {
            auto bytes=v.toByteArray().trimmed();
            if(bytes.isEmpty())
                return qbl_null;
            //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
            else if((vType==QMetaType::QByteArray || vType==QMetaType::QString)){
                auto md5=bytes.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"),qbl_null);
                if(md5.length()==32)
                    return md5;
            }
            return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
        }
    }

    static QByteArray toByteArray(const QVariant &v)
    {
        auto vType=v.typeId();
        if(vType==QMetaType::QVariantList || vType==QMetaType::QStringList || vType==QMetaType::QVariantMap || vType==QMetaType::QVariantHash)
            return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);

        if(vType==QMetaType::QUuid)
            return v.toUuid().toByteArray();

        return v.toByteArray();
    }

    static bool canConvertJson(const QVariant &v, QVariant &vOut)
    {
        vOut=QVariant();
        if(v.isNull() || !v.isValid()){
            return false;
        }

        if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList){
            vOut=v;
            return true;
        }

        if(!(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray)){
            return false;
        }

        {
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr)
                if(doc.isArray() || doc.isObject()){
                    vOut=doc.toVariant();
                    return true;
                }
        }
        return false;
    }

    bool md5ParserUuid(const QString& vtext, QString&outText)const{
        QByteArray suuid;
        auto text=vtext;
        text.replace(qsl("-"),qsl_null).replace(qsl("{"),qsl_null).replace(qsl("}"),qsl_null);
        if(text.length()==32){
            int i=0;
            for(auto&c:text){
                ++i;
                suuid.append(c.toLatin1());
                if(i==8 || i==12 || i==16 || i==20){
                    suuid.append(qbl("-"));
                }
            }
            outText=suuid;
            return true;
        }
        outText=qbl_null;
        return false;
    }

    QUuid md5toUuid(const QString&md5)const{
        auto smd5=md5;
        if(md5ParserUuid(smd5, smd5))
            return QUuid::fromString(qsl("{")+smd5+qsl("}"));

        return QUuid();
    }

    QVariant vUnion(const QVariant &v){
        auto t=v.typeId();
        if(!v.isValid())
            return {};

        if(t==QMetaType::QVariantList || t==QMetaType::QStringList){
            auto vList=v.toList();
            QVariant vA;
            while(!vList.isEmpty()){
                auto vB=vList.takeFirst();
                if(vB.typeId()==vA.typeId()){
                    vA=vUnion(vA,vB);
                }
            }
            return vA;
        }

        return {};
    }

    QVariant vUnion(const QVariant &vDestine, const QVariant &vSource)
    {
        auto t=vDestine.typeId();
        if(vDestine.typeId()!=vSource.typeId())
            return {};

        if(t==QMetaType::QVariantList || t==QMetaType::QStringList)
            return (vDestine.toList()+vSource.toList());

        if(t==QMetaType::QVariantMap || t==QMetaType::QVariantHash){
            auto aMap=vDestine.toHash();
            auto bMap=vSource.toHash();
            QHashIterator<QString, QVariant> i(bMap);
            while (i.hasNext()) {
                i.next();
                const auto&k=i.key();
                if(!aMap.contains(k)){
                    aMap[k]=i.value();
                }
            }
            return aMap;
        }

        {
            QByteArray rByte;
            auto ls=QVariantList{vDestine, vSource};
            for(auto&v:ls){
                rByte.append(v.toByteArray());
            }
            return rByte;
        }
    }

    QVariant vMerge(const QVariant &v){
        QVariant vOut;
        if(this->canConvertJson(v,vOut)){
            auto t=vOut.typeId();
            if(!vOut.isValid())
                return {};
            if(t==QMetaType::QVariantList || t==QMetaType::QStringList){
                auto vList=vOut.toList();
                if(!vList.isEmpty()){
                    auto vA=QVariant(vList.takeFirst());
                    for(const auto&vB:vList){
                        if(vB.typeId()==vA.typeId()){
                            vA=vMerge(vA,vB);
                        }
                    }
                    return vA;
                }
            }
        }
        return {};
    }

    static QVariant vMerge(const QVariant&vDestineIn, const QVariant&vSourceIn){
        QVariant vDestine;
        QVariant vSource;
        if(!canConvertJson(vDestineIn, vDestine))
            vDestine=vDestineIn;

        if(!canConvertJson(vSourceIn, vSource))
            vSource=vSourceIn;

        auto t=vDestine.typeId();
        if(vDestine.typeId()!=vSource.typeId()){
            return {};
        }
        else if(t==QMetaType::QVariantList || t==QMetaType::QStringList){
            auto dst=vDestine.toList();
            auto src=vSource.toList();
            QStringList keyList;
            QVariantList lst;
            for(const auto&v:dst){//cache de chaves existentes
                if(v.isValid()){
                    if( v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList || v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash )
                        keyList<<toMd5(v);
                    else
                        keyList<<toByteArray(v);
                }
            }
            for(auto&v:src){
                if(v.isValid()){
                    QByteArray key;
                    if( v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList || v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash )
                        key=toMd5(v);
                    else
                        key=toByteArray(v);

                    if(!lst.contains(key)){
                        lst<<v;
                    }
                }
            }
            return lst;
        }
        else if(t==QMetaType::QVariantMap || t==QMetaType::QVariantHash){
            auto aMap=vDestine.toHash();
            auto bMap=vSource.toHash();
            QHashIterator<QString, QVariant> i(bMap);
            while (i.hasNext()) {
                i.next();
                const auto&k=i.key();
                const auto&vb=i.value();
                auto&va=aMap[k];
                if(!va.isValid() || va.isNull()){
                    va=vb;
                }
                else{
                    const auto v=vMerge(va,vb);
                    aMap[k]=v;
                }
            }
            return aMap;
        }
        else{
            QByteArray rByte;
            auto ls=QVariantList{vDestine, vSource};
            for(auto&v:ls){
                rByte.append(v.toByteArray());
            }
            return rByte;
        }
        return {};
    }

    QVariant vDeduplicate(const QVariant&v){
        QVariant vRet;
        if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash){
            auto vMap=v.toHash();
            auto vAdd=QVariantHash();
            QHashIterator<QString, QVariant> i(vMap);
            while (i.hasNext()) {
                i.next();
                const auto&key=i.key();//no modifique a chave
                auto value=vDeduplicate(i.value());
                if(vAdd.contains(key))
                    vAdd.insert(key, value);
            }
            vRet=vAdd;
        }
        else if(v.typeId()==QMetaType::QVariantList){
            auto vMap=v.toList();
            auto vAdd=QVariantHash();
            for(auto&v:vMap){
                const auto value=vDeduplicate(v);
                const auto key=toMd5(value);
                if(!vAdd.contains(key))
                    vAdd.insert(key,value);
            }
            vRet=vAdd.values();
        }
        return v;
    }

};

VariantUtil::VariantUtil(const QVariant &v):QVariant(v)
{
    this->p = new VariantUtilPvt(this);
}

VariantUtil::~VariantUtil()
{
    dPvt();
    this->p=nullptr;
    p.deleteLater();
}

VariantUtil&VariantUtil::operator=(const QVariant &v)
{
    this->setValue(v);
    return*this;
}

bool VariantUtil::isHex(const QVariant &v)const
{
    bool __isHex=false;
    for(auto&c:v.toString()){
        if (!isxdigit(c.toLatin1()))
            return false;
        else
            __isHex=true;
    }
    return __isHex;
}

bool VariantUtil::isBase64(const QVariant &v) const
{
    auto bytes=QByteArray::fromBase64(v.toByteArray());
    return !bytes.isEmpty();
}

const QString VariantUtil::toStr(const QVariant &v)
{
    dPvt();
    set__value(v);
    auto vType=int();
    if(vType==QMetaType::QVariantList || vType==QMetaType::QStringList || vType==QMetaType::QVariantMap || vType==QMetaType::QVariantHash)
        return QJsonDocument::fromVariant(*this).toJson(QJsonDocument::Compact);

    if(vType==QMetaType::QUuid)
        return QVariant::toUuid().toString();

    return QVariant::toString();
}

const QByteArray VariantUtil::toByteArray(const QVariant &v)
{
    dPvt();
    set__value(v);
    auto vType=this->typeId();
    if(vType==QMetaType::QVariantList || vType==QMetaType::QStringList || vType==QMetaType::QVariantMap || vType==QMetaType::QVariantHash)
        return QJsonDocument::fromVariant(*this).toJson(QJsonDocument::Compact);

    if(vType==QMetaType::QUuid)
        return QVariant::toUuid().toByteArray();

    return QVariant::toByteArray();
}

const QChar VariantUtil::toChar(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toChar();
}

int VariantUtil::toInt(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toUInt();
}

qlonglong VariantUtil::toLongLong(const QVariant &v)
{
    if(v.isValid()) QVariant::setValue(v);
    return QVariant::toLongLong();
}

const QDate VariantUtil::toDate(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toDate();
}

const QTime VariantUtil::toTime(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toTime();
}

const QDateTime VariantUtil::toDateTime(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toDateTime();
}

double VariantUtil::toDouble(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toDouble();
}

bool VariantUtil::toBool(const QVariant &v)
{
    const static auto listBool=QVector<QByteArray>()<<qbl("1")<<qbl("true")<<qbl("yes")<<qbl("sim")<<qbl("verdadeiro")<<qbl("t")<<qbl("s")<<qbl("v")<<qbl("y");
    dPvt();
    set__value(v);
    if(QVariant::typeId()==QMetaType::Bool)
        return QVariant::toBool();
    else if(listBool.contains(QVariant::toByteArray().toLower().trimmed()))
        return true;
    else
        return false;
}

bool VariantUtil::canConvertJson(const QVariant &v) const
{
    QVariant vOut;
    dPvt();
    return p.canConvertJson(v, vOut);
}

bool VariantUtil::canConvertJson(const QVariant &v, QVariant &vOut) const
{
    dPvt();
    return p.canConvertJson(v, vOut);
}

const QByteArray VariantUtil::toMd5(const QVariant &v)
{
    dPvt();
    set__value(v);
    if(!this->isValid())
        return qbl_null;

    if(this->typeId()==QMetaType::QUuid){
        auto uuid=QVariant::toUuid();
        auto suuid=uuid.toByteArray();
        auto md5=suuid.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
        if(md5.length()==32)
            return md5;
        else
            return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
    }

    {
        auto bytes=this->toByteArray().trimmed();
        if(bytes.isEmpty())
            return qbl_null;
        //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
        else if((this->typeId()==QMetaType::QByteArray || this->typeId()==QMetaType::QString)){
            auto md5=bytes.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
            if(md5.length()==32)
                return md5;
        }
        return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
    }
}

const QByteArray VariantUtil::toHex(const QVariant &v)
{
    dPvt();
    set__value(v);
    return this->toByteArray().toHex();
}

const QUuid VariantUtil::toUuid(const QVariant &v)
{
    dPvt();
    set__value(v);
    if(int()==QMetaType::QUuid)
        return QVariant::toUuid();
    return p.md5toUuid(this->toStr(v));
}

const QUuid VariantUtil::toMd5Uuid(const QVariant &v)
{
    auto md5=this->toMd5(v);
    return this->toUuid(md5);
}

QVVM VariantUtil::toVVM() const
{
    dPvt();
    return p.vvm;
}

const QVVM VariantUtil::toVVM(const QVariant &v)
{
    dPvt();
    if(v.isValid())
        p.clear();
    auto map=VariantUtil::toHash();
    QHashIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        p.vvm.insert(i.key(), i.value());
    }
    return QVVM(p.vvm);
}

const QVVM VariantUtil::toVVM(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    p.vvm.insert(key, value);
    this->setValue(QVariant());
    return QVVM(p.vvm);
}

const QVariantList VariantUtil::takeList(const QByteArray &keyName)
{
    QVariantList la;
    QVariantList lb;
    if(this->typeId()==QMetaType::QVariantList)
        la=this->toList();
    else
        la<<this->toHash();
    for(auto&v:la){
        if((v.typeId()==QMetaType::QVariantMap) || (v.typeId()==QMetaType::QVariantHash)){
            auto vm=v.toHash();
            auto vv=vm.value(keyName);
            if(vv.isValid()){
                lb<<vv;
            }
        }
    }
    return lb;
}

int VariantUtil::typeId() const
{
    dPvt();
    if(!p.vvm.isEmpty())
        return QMetaType::QVariantMap;
    else
        return int();
}

const QStringList VariantUtil::toStringList()
{
    return this->toStringList(*this);
}

const QStringList VariantUtil::toStringList(const QVariant &v)
{
    QStringList map;
    if(v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList)
        map=v.toStringList();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(), error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.toVariant().toStringList();
        }
    }
    return map;
}

const QVariantList VariantUtil::toList(const QVariant &v)
{
    dPvt();
    set__value(v);
    return this->toVariantObject(v).toList();
}

QVariantMap VariantUtil::toMap() const
{
    dPvt();
    if(!p.vvm.isEmpty()){
        QVariantMap map;
        QHashIterator<QString, QVariant> i(p.vvm);
        while (i.hasNext()) {
            i.next();
            map.insert(i.key(), i.value());
        }
        return map;
    }

    auto v=p.toMap(*this);
    return v;
}

QVariantMap VariantUtil::toMap(const QVariant &v)const
{
    QVariantMap map;
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash)
        map=v.toMap();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.object().toVariantMap();
        }
    }
    return map;
}

const QVariantMap VariantUtil::toMap(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.clear();
    this->makeMap(key,value);
    return this->toMap();
}

QVariantHash VariantUtil::toHash()const
{
    dPvt();
    if(!p.vvm.isEmpty()){
        QVariantHash map;
        QHashIterator<QString, QVariant> i(p.vvm);
        while (i.hasNext()) {
            i.next();
            map.insert(i.key(), i.value());
        }
        return map;
    }

    auto v=p.toHash(*this);
    return v;
}

const QVariantHash VariantUtil::toHash(const QVariant &v)
{
    QVariantHash map;
    int vtype=v.typeId();
    if(vtype==QMetaType::QVariantMap || vtype==QMetaType::QVariantHash)
        map=v.toHash();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(vtype==QMetaType::QString || vtype==QMetaType::QByteArray || vtype==QMetaType::QChar || vtype==QMetaType::QBitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.object().toVariantHash();
        }
    }
    return map;
}

const QVariantHash VariantUtil::toHash(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.clear();
    this->makeHash(key,value);
    return this->toHash();
}

QMultiHash<QString, QVariant> VariantUtil::toMultiHash() const
{
    return QMultiHash<QString, QVariant>(this->toHash());
}

const QMultiHash<QString, QVariant> VariantUtil::toMultiHash(const QVariant &v)
{
    return QMultiHash<QString, QVariant>(this->toHash(v));
}

const QMultiHash<QString, QVariant> VariantUtil::toMultiHash(const QVariant &key, const QVariant &value)
{
    return QMultiHash<QString, QVariant>(this->toHash(key, value));
}

const QVariant VariantUtil::toType(int type, const QVariant &v)
{
    dPvt();
    set__value(v);
    if(type==QMetaType::QUuid)
        return this->toUuid(v);

    if(type==QMetaType::QUrl)
        return this->toUrl(v);

    if(type==QMetaType::QString || type==QMetaType::QByteArray  || type==QMetaType::QBitArray || type==QMetaType::QChar)
        return this->toStr(v);

    if(type==QMetaType::QVariantMap || type==QMetaType::QVariantHash)
        return this->toMap(v);

    if(type==QMetaType::QStringList)
        return this->toStringList(v);

    if(type==QMetaType::QVariantList)
        return this->toList(v);

    if(type==QMetaType::Int || type==QMetaType::UInt || type==QMetaType::LongLong || type==QMetaType::ULongLong || type==QMetaType::Double)
        return this->toLongLong(v);

    if(type==QMetaType::QDate)
        return this->toDate(v);

    if(type==QMetaType::QTime)
        return this->toTime(v);

    if(type==QMetaType::QDateTime)
        return this->toDateTime(v);

    if(type==QMetaType::Bool)
        return this->toBool(v);

    return {};
}

const QVariant VariantUtil::toVariant(const QVariant &v)
{
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList){
        return v;
    }

    if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        auto vv=this->toVariantJson(v);
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv.isValid()?vv:vv;
    }

    return v;
}

const QVariant VariantUtil::toVariantObject(const QVariant &v)
{
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList){
        return v;
    }

    if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        auto vv=this->toVariantJson(v);
        if(!(vv.typeId()==QMetaType::QVariantMap || vv.typeId()==QMetaType::QVariantHash || vv.typeId()==QMetaType::QVariantList || vv.typeId()==QMetaType::QStringList)){
            vv=this->toVariantCBor(v);
            if(!(vv.typeId()==QMetaType::QVariantMap || vv.typeId()==QMetaType::QVariantHash || vv.typeId()==QMetaType::QVariantList || vv.typeId()==QMetaType::QStringList)){
                vv=QVariant();
            }
        }
        return vv;
    }

    return {};
}

const QVariant VariantUtil::toVariantJson(const QVariant &v)
{
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList){
        return v;
    }

    if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        auto vv=QJsonDocument::fromJson(v.toByteArray()).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv.isValid()?vv:v;
    }
    return v;
}

const QVariant VariantUtil::toVariantCBor(const QVariant &v)
{
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList){
        return v;
    }

    if(v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar || v.typeId()==QMetaType::QBitArray){
        auto vv=QCborValue::fromVariant(v).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantJson(v);
        return vv.isValid()?vv:v;
    }

    return v;
}

const QUrl VariantUtil::toUrl(const QVariant &v)
{
    if(v.isValid()) QVariant::setValue(v);
    if(v.typeId()==QMetaType::QUrl)
        return v.toUrl();

    QUrl url;
    auto surl=v.toString();
    if(QFile::exists(surl))
        url=QUrl::fromLocalFile(surl);
    else
        url=QUrl(surl);
    QVariant::setValue(url);
    return url;
}

VariantUtil &VariantUtil::makeVVM(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.insert(key, value);
    this->setValue(QVariant());
    return*this;
}

VariantUtil &VariantUtil::mVVM(const QVariant &key, const QVariant &value)
{
    return this->makeVVM(key, value);
}

VariantUtil &VariantUtil::makeMap(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto map=QVariant::toMap();
    map.insert(key.toString(),value);
    this->setValue(map);
    return*this;
}

VariantUtil &VariantUtil::mMap(const QVariant &key, const QVariant &value)
{
    return this->makeMap(key,value);
}

VariantUtil &VariantUtil::makeHash(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto map=QVariant::toHash();
    map.insert(key.toString(),value);
    this->setValue(map);
    return*this;
}

VariantUtil &VariantUtil::mHash(const QVariant &key, const QVariant &value)
{
    return this->makeHash(key,value);
}

VariantUtil &VariantUtil::makeList(const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto list=QVariant::toList();
    list<<value;
    this->setValue(list);
    return*this;
}

VariantUtil &VariantUtil::mList(const QVariant&value)
{
    return this->makeList(value);
}

VariantUtil &VariantUtil::clear()
{
    dPvt();
    p.clear();
    return*this;
}

VariantUtil &VariantUtil::vUnion(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vUnion(v));
    return*this;
}

VariantUtil &VariantUtil::vUnion(const QVariant &vDestine, const QVariant &vSource)
{
    dPvt();
    p.clear();
    this->setValue(p.vUnion(vDestine,vSource));
    return*this;
}

VariantUtil &VariantUtil::vMerge(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vMerge(v));
    return*this;
}

VariantUtil &VariantUtil::vMerge(const QVariant &vDestine, const QVariant &vSource)
{
    dPvt();
    p.clear();
    this->setValue(p.vMerge(vDestine,vSource));
    return*this;
}

VariantUtil &VariantUtil::vDeduplicate(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vDeduplicate(v));
    return*this;
}

bool VariantUtil::vIsEmpty(const QVariant &v)
{
    auto vv=QVariant(v.isValid()?v:*this);
    bool invalid=vv.isValid() && !v.isNull();
    if(!invalid)
        return false;

    if(vv.typeId()==QMetaType::QUuid)
        return vv.toUuid().isNull();

    if(vv.typeId()==QMetaType::QUrl)
        return vv.toUrl().isEmpty();

    if(vv.typeId()==QMetaType::QString || vv.typeId()==QMetaType::QByteArray  || vv.typeId()==QMetaType::QBitArray || vv.typeId()==QMetaType::QChar)
        return vv.toByteArray().trimmed().isEmpty();

    if(vv.typeId()==QMetaType::QVariantMap || vv.typeId()==QMetaType::QVariantHash)
        return vv.toHash().isEmpty();

    if(vv.typeId()==QMetaType::QVariantList || vv.typeId()==QMetaType::QStringList)
        return vv.toList().isEmpty();

    if(QByteArray(vv.typeName())==QT_STRINGIFY2(QVVM))
        return vv.toHash().isEmpty();

    if(vv.typeId()==QMetaType::Int || vv.typeId()==QMetaType::UInt || vv.typeId()==QMetaType::LongLong || vv.typeId()==QMetaType::ULongLong || vv.typeId()==QMetaType::Double)
        return vv.toDouble()==0;

    if(vv.typeId()==QMetaType::QDate || vv.typeId()==QMetaType::QTime || vv.typeId()==QMetaType::QDateTime)
        return vv.toDateTime().isNull();

    return vv.isNull();

}

bool VariantUtil::vIsObject(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList)
        return true;
    if(v.typeId()==QMetaType::QVariantMap || v.typeId()==QMetaType::QVariantHash)
        return true;

    return false;
}

bool VariantUtil::vIsList(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.typeId()==QMetaType::QVariantList || v.typeId()==QMetaType::QStringList);
}

bool VariantUtil::vIsMap(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.typeId()==QMetaType::QVariantHash || v.typeId()==QMetaType::QVariantMap || QByteArray(v.typeName())==QT_STRINGIFY2(QVVM));
}

bool VariantUtil::vIsString(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.typeId()==QMetaType::QString || v.typeId()==QMetaType::QByteArray || v.typeId()==QMetaType::QChar);
}

}
