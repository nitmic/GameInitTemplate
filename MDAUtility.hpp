#pragma once
#include <SmartPointerUtility.hpp>
#include "MDA.h"


/**
*@brief	IModelが有効かどうか. 有効なら関数を呼ぶ.
*@return bool
*@param p    : shared_ptr or weak_ptr, or they are wrapped by vector.
        func : When IModel::isValid return true, it is called.

*/
template<class T>
bool isValid(T & p){
	return isTrue(p, &IModel::isValid);
}
template<class T>
bool isValid(T & p, std::function<void(typename toShared<T>::type &)> func){
	return isTrue(p, func, &IModel::isValid);
}

//std::vector用
template<class T>
void isValid(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrue(v, func, &IModel::isValid);
}

/**
*@brief	IModelが有効かどうか. 有効なら関数を呼び, falseならeraseする.
*@return void
*@param v    : std::vector<shared_ptr or weak_ptr>
        func : When IModel::isValid return true, it is called.
*/
template<class T>
void isValidOrErase(std::vector<T> & v){
	isTrueOrErase(v, doNothing<typename toShared<T>::type>, &IModel::isValid);
}
template<class T>
void isValidOrErase(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrueOrErase(v, func, &IModel::isValid);
}


/**
*@brief	IDrawerが有効かどうか. 有効なら関数を呼ぶ.
*@return bool
*@param p    : shared_ptr or weak_ptr, or they are wrapped by vector.
        func : When IDrawer::isVisible return true, it is called.

*/
template<class T>
bool isVisible(T & p){
	return isTrue(p, &IDrawer::isVisible);
}
template<class T>
bool isVisible(T & p, std::function<void(typename toShared<T>::type &)> func){
	return isTrue(p, func, &IDrawer::isVisible);
}

//std::vector用
template<class T>
void isVisible(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrue(v, func, &IDrawer::isVisible);
}

/**
*@brief	IDrawerが有効かどうか. 有効なら関数を呼び, falseならeraseする.
*@return void
*@param v    : std::vector<shared_ptr or weak_ptr>
        func : When IDrawer::isVisible return true, it is called.
*/
template<class T>
void isVisibleOrErase(std::vector<T> & v){
	isTrueOrErase(v, doNothing<typename toShared<T>::type>, &IDrawer::isVisible);
}
template<class T>
void isVisibleOrErase(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrueOrErase(v, func, &IDrawer::isVisible);
}



/**
*@brief	IAgentが有効かどうか. 有効なら関数を呼ぶ.
*@return bool
*@param p    : shared_ptr or weak_ptr, or they are wrapped by vector.
        func : When IAgent::isAlive return true, it is called.

*/
template<class T>
bool isAlive(T & p){
	return isTrue(p, &IAgent::isAlive);
}
template<class T>
bool isAlive(T & p, std::function<void(typename toShared<T>::type &)> func){
	return isTrue(p, func, &IAgent::isAlive);
}

//std::vector用
template<class T>
void isAlive(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrue(v, func, &IAgent::isAlive);
}

/**
*@brief	IAgentが有効かどうか. 有効なら関数を呼び, falseならeraseする.
*@return void
*@param v    : std::vector<shared_ptr or weak_ptr>
        func : When IAgent::isAlive return true, it is called.
*/
template<class T>
void isAliveOrErase(std::vector<T> & v){
	isTrueOrErase(v, doNothing<typename toShared<T>::type>, &IAgent::isAlive);
}
template<class T>
void isAliveOrErase(std::vector<T> & v, std::function<void(typename toShared<T>::type &)> func){
	isTrueOrErase(v, func, &IAgent::isAlive);
}


template<class T>
void stepping_imp(T & p){
	p->step();
}

template<class T>
void stepping(T & p){
	isAlive(p, stepping_imp<T>);
}

template<class T>
void stepping(std::vector<T> & v){
	isAliveOrErase(v, stepping_imp<T>);
}


template<class T>
void drawing_imp(T & p){
	p->draw();
}

template<class T>
void drawing(T & p){
	isVisible(p, drawing_imp<T>);
}

template<class T>
void drawing(std::vector<T> & v){
	isVisibleOrErase(v, drawing_imp<T>);
}