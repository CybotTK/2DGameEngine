#include "Python/PythonRegistry.h"

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

#include "Engine.h"
#include "Core/Component.h"

#define PY_REFFERENCE py::return_value_policy::reference

App* __GetApp() {
	return App::Get();
}

void PyRegisterMath(py::module_& m) {
	py::module math = m.def_submodule("math");

	py::class_<glm::vec2>(math, "Vector2")
		.def(py::init<>())
		.def(py::init<float>())
		.def(py::init<const glm::vec2&>())
		.def(py::init<float, float>())
		.def_readwrite("x", &glm::vec2::x)
		.def_readwrite("y", &glm::vec2::y)

		.def_readwrite("s", &glm::vec2::x)
		.def_readwrite("t", &glm::vec2::y)

		.def_readwrite("u", &glm::vec2::x)
		.def_readwrite("v", &glm::vec2::y)

		.def(py::self == py::self)
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self - py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(float() * py::self)
		.def(py::self * float())

		// String representation for glm::vec2
		.def("__repr__", [](const glm::vec2& v) {
			return "<Vector2(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")>";
		});


	py::class_<glm::vec3>(math, "Vector3")
		.def(py::init<>())
		.def(py::init<float>())
		.def(py::init<const glm::vec3&>())
		.def(py::init<float, float, float>())
		.def_readwrite("x", &glm::vec3::x)
		.def_readwrite("y", &glm::vec3::y)
		.def_readwrite("z", &glm::vec3::z)

		.def_readwrite("r", &glm::vec3::x)
		.def_readwrite("g", &glm::vec3::y)
		.def_readwrite("b", &glm::vec3::z)
		.def(py::self == py::self)
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self - py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(float() * py::self)
		.def(py::self * float())

		// String representation for glm::vec3
		.def("__repr__", [](const glm::vec3& v) {
			return "<Vector3(" + std::to_string(v.x) + ", " + std::to_string(v.y) 
				+ ", " + std::to_string(v.z) + ")>";
		});

	py::class_<glm::vec4>(math, "Vector4")
		.def(py::init<>())
		.def(py::init<float>())
		.def(py::init<const glm::vec4&>())
		.def(py::init<float, float, float, float>())
		.def_readwrite("x", &glm::vec4::x)
		.def_readwrite("y", &glm::vec4::y)
		.def_readwrite("z", &glm::vec4::z)
		.def_readwrite("w", &glm::vec4::w)

		.def_readwrite("r", &glm::vec4::x)
		.def_readwrite("g", &glm::vec4::y)
		.def_readwrite("b", &glm::vec4::z)
		.def_readwrite("a", &glm::vec4::w)
		.def(py::self == py::self)
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self - py::self)
		.def(py::self -= py::self)
		.def(py::self *= float())
		.def(float() * py::self)
		.def(py::self * float())

		// String represantation for vec4
		.def("__repr__", [](const glm::vec4& v) {
			return "<Vector4(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", "
				+ std::to_string(v.z) + ", " + std::to_string(v.w) + ")>";
		});
}

#define REGISTER_HANDLER(T, NAME)																\
	py::class_<AssetHandler<T>>(m, NAME)														\
		.def(py::init<>())																		\
		.def("add",		&AssetHandler<T>::Add)													\
		.def("set",		(void (AssetHandler<T>::*)(size_t))&AssetHandler<T>::Set)				\
		.def("set",		(void (AssetHandler<T>::*)(T*))&AssetHandler<T>::Set)					\
		.def("set",		(void (AssetHandler<T>::*)(const std::string&))&AssetHandler<T>::Set)	\
		.def("get",		&AssetHandler<T>::Get)													\
		.def("getID",	&AssetHandler<T>::GetID);												\

void PyRegisterEngineCode(py::module_& m) {
	m.def("getApp", __GetApp, PY_REFFERENCE);

	py::class_<App>(m, "App")
		.def_readonly("input",			&App::input, PY_REFFERENCE)
		.def_property("currentScene",	&App::GetCurrentScene, (void(App::*)(const std::string&))&App::SetCurrentScene)
		.def("getDelatTime",			&App::GetDeltaTime)
		.def("getCurrentScene",			&App::GetCurrentScene, PY_REFFERENCE)
		.def("setCurrentScene",			(void(App::*)(const std::string&))&App::SetCurrentScene);

	py::class_<Input>(m, "Input")
		.def("quit",			&Input::ForceQuit)
		.def("pressed",			&Input::Pressed)
		.def("active",			&Input::Active)
		.def("released",		&Input::Released)
		.def("getMouseMotion",	&Input::GetMouseMotion)
		.def("getMouseScroll",	&Input::GetMouseScrollY);

	py::class_<Scene>(m, "Scene")
		.def_readwrite("camera",			&Scene::camera,		PY_REFFERENCE)
		.def_readwrite("layers",			&Scene::layers,		PY_REFFERENCE)
		.def_readwrite("background",	&Scene::background, PY_REFFERENCE)
		.def("getObjects",				&Scene::GetObjectsRecursively)
		.def("getGravity",				&Scene::GetGravity)
		.def("setGravity",				(void (Scene::*)(float, float))&Scene::SetGravity)
		.def("setGravity",				(void (Scene::*)(glm::vec2))&Scene::SetGravity);

	py::class_<Object::_Debug>(m, "ObjectDebugDesc")
		.def_readwrite("name", &Layer::_Debug::name);

	py::class_<Layer>(m, "Layer")
		.def_readwrite("debug",		&Layer::debug)
		.def_readwrite("tint",		&Layer::tint)
		.def_readwrite("useCamera", &Layer::useCamera)
		.def_readwrite("objects",	&Layer::objects)
		.def("addNew",				&Layer::NewObject)
		.def("getLayerIndex",		&Layer::GetLayerIndex)
		.def("moveUp",				&Layer::MoveUp)
		.def("modeDown",			&Layer::MoveDown)
		.def("getObjects",			&Layer::GetObjectsRecursively)
		.def("add",					&Layer::Add, "Adds an objects to the given Layer");

	//==================================================================//
	//						     Asset Type:							//
	//==================================================================//

	py::class_<ImageTexture	>(m, "ImageTexture")
		.def(py::init<>());

	py::class_<Mesh			>(m, "Mesh")
		.def(py::init<>());

	py::class_<AudioTrack	>(m, "AudioTrack")
		.def(py::init<>())
		.def("play", &AudioTrack::Play);

	py::class_<PythonScript	>(m, "PythonScript")
		.def(py::init<>())
		.def_readwrite("code", &PythonScript::code);

	//==================================================================//
	//						Asset Handler related:						//
	//==================================================================//

	REGISTER_HANDLER(ImageTexture,	"ImageTextureHandler");
	REGISTER_HANDLER(Mesh,			"MeshHandler");
	REGISTER_HANDLER(AudioTrack,	"AudioTrackHandler");
	REGISTER_HANDLER(PythonScript,	"PythonScriptHandler");
	REGISTER_HANDLER(Scene,			"SceneHandler");

	//==================================================================//
	//						 Game Object related:						//
	//==================================================================//

	//py::class_<Component, std::unique_ptr<Component, py::nodelete>>(m, "Component")
	py::class_<Component>(m, "Component")
		.def(py::init<GameObject*>())
		.def("start",		&Component::Start)
		.def("update",		&Component::Update)
		.def("end",			&Component::End)
		.def("getOwner",	&Component::GetOwner, PY_REFFERENCE);

	py::enum_<GameObject::PhysicsType>(m, "physicsType")
		.value("GHOST",		GameObject::GHOST)
		.value("STATIC",	GameObject::STATIC)
		.value("DYANMIC",	GameObject::DYNAMIC)
		.export_values();

	py::class_<GameObject::_Sprite>(m, "SpriteDesc")
		.def_readwrite("color",		&GameObject::_Sprite::color)
		.def_readwrite("texture",	&GameObject::_Sprite::texture)
		.def_readwrite("shape",		&GameObject::_Sprite::shape);

	py::class_<GameObject::_Physics>(m, "PhysicsDesc")
		.def_readwrite("type",			&GameObject::_Physics::type)
		.def_readwrite("category",		&GameObject::_Physics::category)
		.def_readwrite("mask",			&GameObject::_Physics::mask)
		.def_readwrite("shapeScale",	&GameObject::_Physics::shapeScale)
		.def_readwrite("fixedRotation", &GameObject::_Physics::fixedRotation)
		.def_readwrite("isBullet",		&GameObject::_Physics::isBullet);

	py::class_<Transform>(m, "Transform")
		.def_readwrite("position",	&Transform::position)
		.def_readwrite("rotation",	&Transform::rotation)
		.def_readwrite("scale",		&Transform::scale);

	py::class_<GameObject, Transform>(m, "GameObject")
		.def_readwrite("debug",			&GameObject::debug)
		.def_readwrite("runLogic",		&GameObject::runLogic)
		.def_readwrite("sprite",		&GameObject::sprite,		PY_REFFERENCE)
		.def_readwrite("physics",		&GameObject::physics,		PY_REFFERENCE)
		.def_readwrite("components",	&GameObject::components,	PY_REFFERENCE)
		.def_property("parent",			&GameObject::GetParent, &GameObject::SetParent, PY_REFFERENCE)
		.def_property("layer",			&GameObject::GetLayer,	&GameObject::SetLayer, PY_REFFERENCE)
		.def("reloadPhysics",			&GameObject::ReloadPhysics)
		.def("getRoot",					&GameObject::GetRoot,		PY_REFFERENCE)
		.def("getScene",				&GameObject::GetScene,		PY_REFFERENCE)
		.def("removeParent",			&GameObject::RemoveParent)
		.def("isInitialized",			&GameObject::IsInitialized)
		.def("kill",					&GameObject::Kill);

	py::class_<Camera, Transform>(m, "Camera")
		.def_readwrite("area", &Camera::area);

	//==================================================================//
	//							   Misc classes:						//
	//==================================================================//

	py::class_<Timer>(m, "Timer")
		.def_property("elapsed",	&Timer::Get, &Timer::Set)
		.def("get",					&Timer::Get)
		.def("set",					&Timer::Set)
		.def("reset",				&Timer::Reset);
	
}
