// 20260929.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

template <typename T>
class PoolHandle {
	friend class ObjectPool<T>;
	explicit PoolHandle(T*obj,ObjectPool<T>*pool)
		:obj_(obj),pool_(pool){ }
public:
	//コピー禁止
	PoolHandle(const PoolHandle&) = delete;
	//ムーブ禁止
	PoolHandle(PoolHandle&& other)noexcept
		:obj_(other.obj), pool_(other.pool) {
		other.obj_ = nullptr;
		other.pool_ = nullptr;
	}

	//デストラクタで自動返却
	~PoolHandle()
	{
		if (obj_ && pool_) {
			pool_->Release(obj_);
		}
	}

	//アクセス演算子
	T* operator->() { return obj_; }
	T& operator*() { return*obj_; }
private:
	T* obj_;
	ObjectPool<T>* pool_;

};