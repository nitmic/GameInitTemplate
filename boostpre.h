#pragma once
#include <array>
#include <map>
#include <Windows.h>
#include <boost\numeric\ublas\vector.hpp>
#include <cmath>
#include <boost/algorithm/clamp.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/math/constants/constants.hpp>

namespace Blas{
	using namespace boost::numeric::ublas;
	typedef bounded_vector<float, 3> Vector3f;
	typedef bounded_vector<float, 2> Vector2f;
	template <class V1, class V2>
	boost::numeric::ublas::vector<typename boost::numeric::ublas::promote_traits<typename V1::value_type,
																				 typename V2::value_type>::promote_type>
	cross_prod(const V1& lhs, const V2& rhs)
	{
		BOOST_UBLAS_CHECK(lhs.size() == 3, boost::numeric::ublas::external_logic());
		BOOST_UBLAS_CHECK(rhs.size() == 3, boost::numeric::ublas::external_logic());

		typedef typename boost::numeric::ublas::promote_traits<typename V1::value_type,
															   typename V2::value_type>::promote_type promote_type;

		boost::numeric::ublas::vector<promote_type> temporary(3);

		temporary(0) = lhs(1) * rhs(2) - lhs(2) * rhs(1);
		temporary(1) = lhs(2) * rhs(0) - lhs(0) * rhs(2);
		temporary(2) = lhs(0) * rhs(1) - lhs(1) * rhs(0);

		return temporary;
	}
	
	Vector2f normalize2(const Vector2f& v){
		return v / norm_2(v);
	}
	Vector3f normalize3(const Vector3f& v){
		return v / norm_2(v);
	}

	float angle(const Vector3f& v, const Vector3f& u){
		const auto length = norm_2(v) * norm_2(u);
	    if (boost::geometry::math::equals(length, static_cast<float>(0.0))) {
	        return static_cast<float>(0.0);
	    }

	    const auto x = inner_prod(v, u) / length;
	    const auto rounded = boost::algorithm::clamp(x, static_cast<float>(-1.0), static_cast<float>(1.0));
	    return std::acos(rounded);
	}
};

