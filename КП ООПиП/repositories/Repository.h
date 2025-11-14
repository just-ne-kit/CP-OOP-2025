#pragma once

#include <memory>
#include <vector>
#include <algorithm>

template<class T>
class Repository {
protected:
    std::vector<std::shared_ptr<T>> m_objects;

    template<typename Lambda>
    const std::shared_ptr<T> find(Lambda&& lambda) const {
        for (const auto& obj : m_objects)
            if (lambda(obj))
                return obj;
        return nullptr;
    }

public:
    Repository(const std::vector<std::shared_ptr<T>>& objects)
        : m_objects(objects) {
    }

    const std::vector<std::shared_ptr<T>>& getAll() const {
        return m_objects;
    }

    template<typename Lambda>
    bool add(const std::shared_ptr<T>& obj, Lambda&& lambda) {
        if (!exists(lambda)) {
            m_objects.push_back(obj);
            return true;
        }
        return false;
    }

    template<typename Lambda>
    const std::shared_ptr<T> get(Lambda&& lambda) const {
        return find(std::forward<Lambda>(lambda));
    }

    template<typename Lambda>
    bool exists(Lambda&& lambda) const {
        return find(std::forward<Lambda>(lambda)) != nullptr;
    }

    template<typename Lambda>
    bool remove(Lambda&& lambda) {
        auto it = std::remove_if(m_objects.begin(), m_objects.end(),
            [&](const std::shared_ptr<T>& obj) { return lambda(obj); });
        if (it != m_objects.end()) {
            m_objects.erase(it, m_objects.end());
            return true;
        }
        return false;
    }

    template<typename Lambda>
    bool update(Lambda&& lambda, const std::shared_ptr<T>& newObj) {
        for (auto& obj : m_objects) {
            if (lambda(obj)) {
                obj = newObj;
                return true;
            }
        }
        return false;
    }
};
