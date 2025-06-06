/// @ref gtx_transform
/// @file glm/gtx/transform.hpp
///
/// @see core (dependence)
/// @see gtc_matrix_transform (dependence)
/// @see gtx_transform
/// @see gtx_transform2
///
/// @defgroup gtx_transform GLM_GTX_transform
/// @ingroup gtx
///
/// Include <glm/gtx/transform.hpp> to use the features of this extension.
///
/// Add transformation matrices

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/matrix_transform.hpp"

namespace glm
{
	/// @addtogroup gtx_
	/// 
	/// 
	/// @{

	/// Transforms a matrix with a translation 4 * 4 matrix created from 3 scalars.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> translate(
		vec<3, T, Q> const& v);

	/// Builds a rotation 4 * 4 matrix created from an axis of 3 scalars and an angle expressed in radians.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> rotate(
		T angle,
		vec<3, T, Q> const& v);

	/// Transforms a matrix with a scale 4 * 4 matrix created from a vector of 3 components.
	/// @see gtc_matrix_transform
	/// @see gtx_transform
	template<typename T, qualifier Q>
	GLM_FUNC_DECL mat<4, 4, T, Q> scale(
		vec<3, T, Q> const& v);

	/// @}
}// namespace glm

#include "transform.inl"
