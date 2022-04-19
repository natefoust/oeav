#pragma once

// stl
#include <mutex>

// boost
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

template<typename Inst>
class FactoryHelper {
public:
	static Inst* createInstance();
};

template<typename Inst> void doNotCallMe();

#define BIND_INSTANCE(InterfaceClass, InstanceClass) \
	template<> \
	static InterfaceClass* FactoryHelper<InterfaceClass>::createInstance() { \
        return new InstanceClass(); \
    } \
    \
    template<> void doNotCallMe<InterfaceClass>() { \
        InstanceFactory<InterfaceClass>::getInstance(); \
    }

template<typename Inst>
class InstanceFactory : boost::noncopyable
{
public:
	static Inst* getInstance()
	{
		std::lock_guard<std::mutex> lock(_rMutex);
		static boost::scoped_ptr<Inst> _instance(FactoryHelper<Inst>::createInstance());

		return _instance.get();
	}

private:
	static std::mutex _rMutex;
};

template<typename Inst>
std::mutex InstanceFactory<Inst>::_rMutex;
