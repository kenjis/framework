
extern zend_class_entry *ice_db_dbinterface_ce;

ZEPHIR_INIT_CLASS(Ice_Db_DbInterface);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_findone, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_find, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_select, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_insert, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_update, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, filters)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db_dbinterface_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, from)
	ZEND_ARG_INFO(0, filters)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ice_db_dbinterface_method_entry) {
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, findOne, arginfo_ice_db_dbinterface_findone)
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, find, arginfo_ice_db_dbinterface_find)
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, select, arginfo_ice_db_dbinterface_select)
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, insert, arginfo_ice_db_dbinterface_insert)
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, update, arginfo_ice_db_dbinterface_update)
	PHP_ABSTRACT_ME(Ice_Db_DbInterface, remove, arginfo_ice_db_dbinterface_remove)
  PHP_FE_END
};
