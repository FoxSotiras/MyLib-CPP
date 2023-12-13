#include <cstring>
#include <initializer_list>
namespace mylib
{
    template<typename T>
    class dynamic_array
    {
        private:
            using llong = long long;
            using ullong = unsigned long long;
            using ushort = unsigned short;

            T* _M_first_elem = nullptr;
            T* _M_last_elem = nullptr;
            ullong _M_array_len = 0;
            static const ushort _M_len_delta = 10;

            constexpr void _M_reallocate(ullong len = _M_len_delta)
            {
                _M_array_len += len;
                T* new_array = new T[_M_array_len];
                std::memcpy(new_array, _M_first_elem, sizeof(T) * (_M_array_len - len));

                delete[] _M_first_elem;
                _M_first_elem = new_array;
                _M_last_elem = _M_first_elem + (_M_array_len - _M_len_delta);
            }
        public:
            constexpr dynamic_array(const ullong& len = _M_len_delta)
            {
                _M_array_len = len;
                _M_first_elem = new T[_M_array_len];
                _M_last_elem = _M_first_elem;
            }

            constexpr dynamic_array(const dynamic_array& other) : dynamic_array(other._M_array_len)
            {
                for (ullong i = 0; i < _M_array_len; ++i)
                {
                    push_back(other[i]);
                }
            }

            constexpr dynamic_array(std::initializer_list<T> list) : dynamic_array(list.size() + _M_len_delta)
            {
                const T* temp = list.begin();

                for (ullong i = 0; i < _M_array_len; ++i)
                {
                    push_back(temp[i]);
                }
            }

            ~dynamic_array()
            {
                delete[] _M_first_elem;
            }

            constexpr T& operator [] (ullong index) const
            {
                return _M_first_elem[index];
            }

            constexpr dynamic_array& operator = (const dynamic_array& other)
            {
                _M_last_elem = _M_first_elem;
                for (ullong i = 0; i < other._M_array_len; ++i)
                {
                    push_back(other[i]);
                }

                return *this;
            }

            constexpr dynamic_array& operator = (std::initializer_list<T> list)
            {
                const T* temp = list.begin();

                _M_last_elem = _M_first_elem;
                for (ullong i = 0; i < list.size(); ++i)
                {
                    push_back(temp[i]);
                }

                return *this;
            }

            constexpr T* data()
            {
                return _M_first_elem;
            }

            constexpr const T* data() const
            {
                return _M_first_elem;
            }

            constexpr const ullong size() const
            {
                return _M_last_elem - _M_first_elem;
            }

            constexpr const ullong max_size() const
            {
                return _M_array_len;
            }

            constexpr void reserve(const ullong& len = _M_len_delta)
            {
                _M_reallocate(len);
            }

            constexpr const ullong capacity() const
            {
                return max_size() - size();
            }

            constexpr void shrink_to_fit()
            {
                if (capacity() == 0)
                {
                    return;
                }

                _M_array_len -= capacity();
                T* new_array = new T[_M_array_len];
                std::memcpy(new_array, _M_first_elem, sizeof(T) * _M_array_len);

                delete[] _M_first_elem;
                _M_first_elem = new_array;
                _M_last_elem = _M_first_elem + _M_array_len;
            }

            constexpr T* begin()
            {
                return _M_first_elem;
            }

            constexpr const T* begin() const
            {
                return _M_first_elem;
            }

            constexpr T* end()
            {
                return _M_last_elem;
            }

            constexpr const T* end() const
            {
                return _M_last_elem;
            }

            constexpr void clear()
            {
                _M_last_elem = _M_first_elem;
            }

            constexpr void insert(ullong index, const T elem)
            {
                if (size() == max_size())
                {
                    _M_reallocate();
                }

                for (ullong i = 0; i < size(); ++i)
                {
                    _M_first_elem[size() - i] = _M_first_elem[size() - i - 1];
                }
                _M_first_elem[index] = elem;
                ++_M_last_elem;
            }

            constexpr void insert(ullong index, ullong cnt, const T elem)
            {
                for (ullong i = 0; i < cnt; ++i)
                {
                    insert(index + i, elem);
                }
            }

            constexpr void insert(ullong index, std::initializer_list<T> list)
            {
                const T* temp = list.begin();
                ullong temp_size = list.size();

                for (ullong i = 0; i < temp_size; ++i)
                {
                    insert(index + i, temp[i]);
                }
            }

            constexpr void erase(ullong index, ullong len = -1)
            {
                if (len >= size() - index)
                {
                    _M_last_elem -= size() - index;
                }
                else
                {
                    for (ullong i = 0; i < size() - len - index; ++i)
                    {
                        _M_first_elem[index + i] = _M_first_elem[i + index + len];
                    }
                    _M_last_elem -= len;
                }
            }

            constexpr void push_back(const T elem)
            {
                if (size() == max_size())
                {
                    _M_reallocate();
                }

                *_M_last_elem = elem;
                ++_M_last_elem;
            }

            constexpr void pop_back()
            {
                --_M_last_elem;
            }
    };
}
