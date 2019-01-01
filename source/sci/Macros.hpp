#ifndef MACROS_HPP
#define MACROS_HPP

#define MANAGER_STATIC_GET_TYPE(type) static ManagerType::Enum get_type() { return type; }
#define MANAGER_LOG(msg) get_application().get_manager<Logger>().log(__FILE__, __LINE__, __FUNCTION__, msg)

#define COMPONENT_STATIC_GET_TYPE(type) static ComponentType::Enum get_type() { return type; }

#define UNUSED(x) static_cast<void>(x);

#endif
