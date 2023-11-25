#include <cstring>
#include <initializer_list>
namespace mylib
{
    template<typename T>
    class dynamic_array
    {
        private:
            typedef long long llong;
            typedef unsigned long long ullong;
            typedef unsigned short ushort;

            T* _first_elem = nullptr;
            T* _last_elem = nullptr;
            ullong _array_len = 0;
            static const ushort _len_delta = 10;

            constexpr void _reallocate(llong _len = _len_delta)
            {
                _array_len += _len;
                T* _new_array = new T[_array_len];
                std::memcpy(_new_array, _first_elem, sizeof(T) * (_array_len - _len_delta));

                delete[] _first_elem;
                _first_elem = _new_array;
                _last_elem = _first_elem + (_array_len - _len_delta);
            }

            constexpr void _default_init(ullong _len)
            {
                _array_len = _len;
                _first_elem = new T[_array_len];
                _last_elem = _first_elem;
            }

            constexpr void _dynamic_array_init(const dynamic_array& _other)
            {
                _array_len = _other._array_len;
                _default_init(_array_len);

                for(int i = 0; i < _array_len; ++i)
                {
                    push_back(_other[i]);
                }
            }

            constexpr void _initializer_list_init(std::initializer_list<T> _list)
            {
                _array_len = _list.size();
                _default_init(_array_len);
                const T* _temp = _list.begin();

                for(int i = 0; i < _array_len; ++i)
                {
                    push_back(_temp[i]);
                }
            }

        public:
            constexpr dynamic_array(ullong len = _len_delta)
            {
                _default_init(len);
            }

            constexpr dynamic_array(const dynamic_array& other)
            {
                _dynamic_array_init(other);
            }

            constexpr dynamic_array(std::initializer_list<T> list)
            {
                _initializer_list_init(list);
            }

            constexpr T& operator [] (ullong index) const
            {
                return _first_elem[index];
            }

            constexpr dynamic_array& operator = (const dynamic_array& other)
            {
                delete[] _first_elem;
                _dynamic_array_init(other);

                return *this;
            }

            constexpr dynamic_array& operator = (std::initializer_list<T> list)
            {
                delete[] _first_elem;
                _initializer_list_init(list);

                return *this;
            }

            constexpr ullong size() const
            {
                return _last_elem - _first_elem;
            }

            constexpr ullong max_size() const
            {
                return _array_len;
            }

            constexpr void push_back(T elem)
            {
                if (size() == max_size())
                {
                    _reallocate();
                }

                *_last_elem = elem;
                ++_last_elem;
            }

            constexpr void pop_back()
            {
                *_last_elem = 0;
                --_last_elem;
            }
    };
}
