#pragma once

#include <boost/noncopyable.hpp>

template<typename Inst>
class InstanceFactory : boost::noncopyable
{
public:
	static Inst* getInstance();
};