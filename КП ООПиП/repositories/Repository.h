#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

template<class T>
class Repository {
protected:
    std::vector<std::shared_ptr<T>> m_objects;

    std::shared_ptr<T> find(const std::function<bool(const std::shared_ptr<T>&)>& pred) const {
        for (const auto& obj : m_objects)
            if (pred(obj))
                return obj;
        return nullptr;
    }

public:
    using Predicate = std::function<bool(const std::shared_ptr<T>&)>;
    using Comparator = std::function<bool(const std::shared_ptr<T>&, const std::shared_ptr<T>&)>;

    explicit Repository(const std::vector<std::shared_ptr<T>>& objects = {})
        : m_objects(objects) {
    }

    const std::vector<std::shared_ptr<T>>& getAll() const {
        return m_objects;
    }

    std::size_t count() const {
        return m_objects.size();
    }

    bool add(const std::shared_ptr<T>& obj, const Predicate& pred) {
        if (!exists(pred)) {
            m_objects.push_back(obj);
            return true;
        }
        return false;
    }

    std::shared_ptr<T> get(const Predicate& pred) const {
        return find(pred);
    }

    bool exists(const Predicate& pred) const {
        return find(pred) != nullptr;
    }

    bool remove(const Predicate& pred) {
        auto it = std::remove_if(m_objects.begin(), m_objects.end(),
            [&](const std::shared_ptr<T>& obj) { return pred(obj); });
        if (it != m_objects.end()) {
            m_objects.erase(it, m_objects.end());
            return true;
        }
        return false;
    }

    bool update(const Predicate& pred, const std::shared_ptr<T>& newObj) {
        for (auto& obj : m_objects) {
            if (pred(obj)) {
                obj = newObj;
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<T> operator[](std::size_t index) {
        return m_objects.at(index);
    }

    void sort(const Comparator& comp) {
        std::sort(m_objects.begin(), m_objects.end(), comp);
    }
};
