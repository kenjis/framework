
extern zend_class_entry *ice_db_ce;

ZEPHIR_INIT_CLASS(Ice_Db);

PHP_METHOD(Ice_Db, getDriver);
PHP_METHOD(Ice_Db, __construct);
PHP_METHOD(Ice_Db, __call);

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, driver, Ice\\Db\\DbInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ice_db___call, 0, 0, 1)
	ZEND_ARG_INFO(0, method)
	ZEND_ARG_INFO(0, arguments)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ice_db_method_entry) {
	PHP_ME(Ice_Db, getDriver, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Ice_Db, __construct, arginfo_ice_db___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Ice_Db, __call, arginfo_ice_db___call, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
