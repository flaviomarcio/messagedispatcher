#pragma once

#include "./private/p_qorm_model_report.h"

namespace QOrm{

    /**
     * @brief The ModelReport class
     */
    template <class T=QOrm::Model>
    class ModelReport : public PrivateQOrm::ModelReportBase
    {
    public:
        Q_INVOKABLE explicit ModelReport(QObject *parent = nullptr) : PrivateQOrm::ModelReportBase(parent), p_dao(this), p_model(this){
            this->init();
        }

        Q_INVOKABLE explicit ModelReport(const QVariant&reportBody, QObject *parent = nullptr)
            :
            PrivateQOrm::ModelReportBase(reportBody, parent)
            , p_dao(this)
            , p_model(this)
        {
            this->init();
        }

        virtual ResultValue &reportfy(){
            this->p_dto.type(this->type());
            this->p_dto.layout(this->layout());
            return PrivateQOrm::ModelReportBase::reportfy();
        }

    private:
        ModelDao<T> p_dao;
        T p_model;
        QOrm::ModelDto&p_dto=this->dto();
        void init(){
            this->dto().initDescriptors(&p_model);
            const auto&modelInfo=p_dao.modelRef;
            this->reportName(modelInfo.modelName()).reportDescription(modelInfo.modelDescription());
        }
    protected:
        virtual const QOrm::ModelInfo&modelInfo(){
            const auto&modelInfo=this->p_model.modelInfo();
            return modelInfo;
        }

        /**
         * @brief search
         * @param value
         * @return
         */
        virtual ResultValue &search(const T&model){
            auto value=model.toMapPKValues();
            VariantUtil util;
            if(!this->options().searchOnEmptyFilter() && util.vIsEmpty(value))
                return this->lr();
            else if(!this->p_dao.recordList(value))
                return this->lr(this->p_dao.lr());
            else{
                auto vList=this->p_dao.lr().resultList();
                vList=this->p_model.toList(vList);
                return this->lr(vList);
            }
        }
        virtual ResultValue &search(const QVariant&value){
            VariantUtil util;
            if(!this->options().searchOnEmptyFilter() && util.vIsEmpty(value))
                return this->lr();
            else if(!this->p_dao.recordList(value))
                return this->lr(this->p_dao.lr());
            else{
                auto vList=this->p_dao.lr().resultList();
                vList=this->p_model.toList(vList);
                return this->lr(vList);
            }
        }
        virtual ResultValue &search(){
            T model(this->source());
            auto mapSource=this->source().toHash();
            SearchParameters map;
            if(!mapSource.isEmpty()){
                const QOrm::ModelInfo&modelInfo=p_dao.modelRef;
                const auto&propertyShortVsTable=modelInfo.propertyShortVsTable();
                QHashIterator<QString, QVariant> i(model.toHash());
                while (i.hasNext()) {
                    i.next();
                    auto header=this->p_dto.headers().get(i.key());
                    if(header!=nullptr){
                        auto vHash=header->filtrableStrategy();
                        auto keywordOperator=vHash.value(qsl("operator"));
                        QString format=vHash.value(qsl("format")).toString().trimmed();
                        QVariant v_value;
                        if(format.contains(qsl("%1")))
                            v_value=format.arg(i.value().toString());
                        else
                            v_value=i.value();
                        if(mapSource.contains(i.key())){
                            auto v_key=propertyShortVsTable.value(i.key());
                            auto a=SqlParserItem::createObject(v_key);
                            auto b=SqlParserItem::createValue(v_value);
                            map.insert(a, b, keywordOperator);
                        }
                    }
                }
            }
            auto v=map.buildVariant();
            return this->search(v);
        }

        auto&onBefore(ModelActionMethod method){
            auto obj=PrivateQOrm::ModelReportBase::onBefore(method);
            return*(dynamic_cast<ModelReport<T>*>(obj));
        }
        auto&onSuccess(ModelActionMethod method){
            auto obj=PrivateQOrm::ModelReportBase::onSuccess(method);
            return*(dynamic_cast<ModelReport<T>*>(obj));
        }
        auto&onFailed(ModelActionMethod method){
            auto obj=PrivateQOrm::ModelReportBase::onFailed(method);
            return*(dynamic_cast<ModelReport<T>*>(obj));
        }
    };

}
