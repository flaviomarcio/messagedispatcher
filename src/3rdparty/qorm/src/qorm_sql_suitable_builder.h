#pragma once

#include "./qorm_object_db.h"
#include "./qorm_sql_suitable_types.h"
#include "./private/p_qorm_sql_suitable_parser_strategy.h"

namespace QOrm {
    class Query;

    class Q_ORM_EXPORT SqlSuitableBuilder : public ObjectDb
    {
    public:
        explicit SqlSuitableBuilder(Query *parent=nullptr);
        Q_INVOKABLE ~SqlSuitableBuilder();

        /**
         * @brief insert
         * @return
         */
        SqlParserInsert &insert();

        /**
         * @brief update
         * @return
         */
        SqlParserUpdate &update();

        /**
         * @brief upsert
         * @return
         */
        SqlParserUpsert &upsert();

        /**
         * @brief exclusion
         * @return
         */
        SqlParserRemove &remove();

        /**
         * @brief select
         * @return
         */
        SqlParserSelect &select();

        /**
         * @brief procedure
         * @return
         */
        SqlParserProcedure &procedure();

        /**
         * @brief function
         * @return
         */
        SqlParserFunction &function();

        /**
         * @brief structure
         * @return
         */
        SqlParserStructure &structure();

        /**
         * @brief combineSelect
         * @return
         */
        SqlParserCombineSelect &combineSelect();


        /**
         * @brief build
         * @return
         */
        virtual bool build();

        /**
         * @brief preparedQuery
         * @return
         */
        QStringList&preparedQuery() const;

        /**
         * @brief clear
         */
        virtual void clear();
    private:
        void*p=nullptr;
    };

}

