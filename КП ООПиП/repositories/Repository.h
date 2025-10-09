#pragma once

#include <memory>
#include <vector>

template<class T>
class Repository
{
protected:
	std::vector<std::shared_ptr<T>> m_objects;

	template<typename Lambda>
	const std::shared_ptr<T> find(Lambda&& lambda) const {
		for (const auto& client : m_objects)
			if (lambda(client))
				return client;
		return nullptr;
	}
public:
	Repository(const std::vector<std::shared_ptr<T>>& objects)
		: m_objects(objects) {
	}

	//Вернет false если имя занято
	template<typename Lambda>
	bool add(const std::shared_ptr<T>& obj, Lambda&& lambda) { return !exists(lambda) ? (m_objects.push_back(obj), true) : false; }

	const std::vector<std::shared_ptr<T>> getAll() const { return m_objects; }

	template<typename Lambda>
	const std::shared_ptr<T> get(Lambda&& lambda) const { return find(lambda); }

	template<typename Lambda>
	const bool exists(Lambda&& lambda) const { return find(lambda) != nullptr; }
};