#pragma once
/*
    noncopyable被繼承後，派生類對象可以被正常的構造和析構，但是無法拷貝構造和賦值操作
*/
class noncopyable{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
private:
    noncopyable() = default;
    ~noncopyable() = default;
};