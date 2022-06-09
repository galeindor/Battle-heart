#pragma once

#include <unordered_map>

 template <typename T, typename U> 
 class HashTable 
 {
 public:
	 HashTable(std::unordered_map<T,U> map);
	~HashTable() = default;

	void setKey(T key , U val) { this->m_map[key] = val; }
	U getVal(T key) { return this->m_map[key]; }
 private:
	 std::unordered_map<T, U> m_map;
};


 template<typename T, typename U>
 inline HashTable<T, U>::HashTable(std::unordered_map<T, U> map)
	 : m_map(map)
 {}
