#pragma once
template <typename T>
class ObjectPool;

template <typename T>
class PoolHandle
{
	friend class ObjectPool<T>;
private:
	explicit PoolHandle(T* obj, ObjectPool<T>* pool)
		:obj_(obj), pool_(pool) {
	}

public:
	//コピー禁止
	PoolHandle(const PoolHandle&) = delete;
	PoolHandle& operator=(const PoolHandle&) = delete;

	//ムーブ禁止
	PoolHandle(PoolHandle&& other)noexcept
		:obj_(other.obj), pool_(other.pool)
	{
		other.obj_ = nullptr;
			other.pool_ = nullptr;
	}

	PoolHandle& operator=(PoolHandle&&) = delete;

	//デストラクタで自動返却
	~PoolHandle();
	T* operator->() { return obj_; }
	const T* operator->()const { return obj_; }
	T& operator*() { return*obj_; }
	const T& operator*()const { return*obj_; }



private:
	T* obj_=nullptr;
	ObjectPool<T>* pool_=nullptr;

};

