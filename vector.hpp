#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"
#include <iostream>
#include <climits>
#include <cstddef>

namespace sjtu
{
    /**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template <typename T>
    class vector
    {
    private:
        T **store = nullptr;
        int _size;
        int cap;
        bool full()
        {
            return _size == cap;
        }

    public:
        /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
        /**
     * you can see RandomAccessIterator at CppReference for help.
     */
        class const_iterator;
        class iterator
        {
            //friend class const_iterator;
            friend class vector;

        private:
            vector<T> *p;
            long long index;

        public:
            /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
            iterator(vector<T> *pv, long long idx) : p(pv), index(idx){};

            iterator operator+(const int &n) const
            {
                return iterator(p, index + n);
            }
            iterator operator-(const int &n) const
            {
                return iterator(p, index - n);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                if (this->p != rhs.p)
                    throw invalid_iterator();
                return this->index - rhs.index;
            }
            iterator &operator+=(const int &n)
            {
                index += n;
                return *this;
            }
            iterator &operator-=(const int &n)
            {
                index -= n;
                return *this;
            }

            iterator operator++(int)
            {
                iterator tmp = *this;
                index++;
                return tmp;
            }

            iterator &operator++()
            {
                index++;
                return *this;
            }

            iterator operator--(int)
            {
                iterator tmp = *this;
                index--;
                return tmp;
            }

            iterator &operator--()
            {
                index--;
                return *this;
            }

            T &operator*() const
            {
                return *(p->store[index]);
            }

            bool operator==(const iterator &rhs) const
            {
                if (p == rhs.p && index == rhs.index)
                    return true;
                else
                    return false;
            }
            bool operator==(const const_iterator &rhs) const
            {
                if (p == rhs.constp &&index = rhs.index)
                    return true;
                else
                    return false;
            }

            bool operator!=(const iterator &rhs) const
            {
                if (p != rhs.p || index != rhs.index)
                    return true;
                else
                    return false;
            }
            bool operator!=(const const_iterator &rhs) const
            {
                if (p != rhs.constp || index != rhs.index)
                    return true;
                else
                    return false;
            }
        };
        /**
     * TODO
     * has same function as iterator, just for a const object.
     */
        class const_iterator
        {
            friend class vector;
        private:
            const vector<T> *constp;
            long long index;

        public:
            const_iterator(const vector<T> *pv, long long idx) : constp(pv), index(idx){};

            const_iterator operator+(const int &n) const
            {
                return const_iterator(constp, index + n);
            }
            const_iterator operator-(const int &n) const
            {
                return const_iterator(constp, index - n);
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                if (this->p != rhs.constp)
                    throw invalid_iterator();
                return this->index - rhs.index;
            }
            const_iterator &operator+=(const int &n)
            {
                index += n;
                return *this;
            }
            const_iterator &operator-=(const int &n)
            {
                index -= n;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                index++;
                return tmp;
            }

            const_iterator &operator++()
            {
                index++;
                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator tmp = *this;
                index--;
                return tmp;
            }

            const_iterator &operator--()
            {
                index--;
                return *this;
            }

            T &operator*() const
            {
                return *(constp->store[index]);
            }

            bool operator==(const iterator &rhs) const
            {
                if (constp == rhs.p &&index = rhs.index)
                    return true;
                else
                    return false;
            }
            bool operator==(const const_iterator &rhs) const
            {
                if (constp == rhs.constp &&index = rhs.index)
                    return true;
                else
                    return false;
            }

            bool operator!=(const iterator &rhs) const
            {
                if (constp != rhs.p || index != rhs.index)
                    return true;
                else
                    return false;
            }
            bool operator!=(const const_iterator &rhs) const
            {
                if (constp != rhs.constp || index != rhs.index)
                    return true;
                else
                    return false;
            }
        };
        /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
        vector() : _size(0), cap(4)
        {
            store = new T *[4];
        }
        vector(const vector &other) : _size(other._size), cap(other.cap)
        {
            store = new T *[cap];
            for (int i = 0; i < _size; i++)
                store[i] = new T(*(other.store[i]));
        }
        ~vector()
        {
            for (int i = 0; i < _size; i++)
                delete store[i];
            delete[] store;
        }
        /**
     * TODO Assignment operator
     */
        vector &operator=(const vector &other)
        {
            if (this == &other)
                return *this;
            for (int i = 0; i < _size; i++)
                delete store[i];
            delete[] store;
            _size = other._size;
            cap = other.cap;
            store = new T *[cap];
            for (int i = 0; i < _size; i++)
                store[i] = new T(*(other.store[i]));
            return *this;
        }
        void doublesize()
        {
            cap *= 2;
            T **newspace = new T *[cap];
            //memcpy(newspace, store, sizeof(T) * cap / 2);
            for (int i = 0; i < _size; i++)
                newspace[i] = store[i];
            delete[] store;
            store = newspace;
        }

        void shrink()
        {
            if (cap > 4)
            {
                cap = std::max(4, cap / 2);
                T **newspace = new T *[cap];
                for (int i = 0; i < _size; i++)
                    newspace[i] = store[i];
                delete[] store;
                store = newspace;
            }
        }
        
        /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
        T &at(const size_t &pos)
        {
            if (pos >= _size)
                throw index_out_of_bound();
            return *(store[pos]);
        }
        const T &at(const size_t &pos) const
        {
            if (pos >= _size)
                throw index_out_of_bound();
            return *(store[pos]);
        }
        /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
        T &operator[](const size_t &pos)
        {
            if (pos >= _size)
                throw index_out_of_bound();
            return *(store[pos]);
        }
        const T &operator[](const size_t &pos) const
        {
            if (pos >= _size)
                throw index_out_of_bound();
            return *(store[pos]);
        }
        /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
        const T &front() const
        {
            if (_size == 0)
                throw container_is_empty();
            return *(store[0]);
        }
        /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
        const T &back() const
        {
            if (_size == 0)
                throw container_is_empty();
            return *(store[_size - 1]);
        }
        /**
     * returns an iterator to the beginning.
     */
        iterator begin()
        {
            return iterator(this, 0);
        }
        const_iterator cbegin() const
        {
            return const_iterator(this, 0);
        }
        /**
     * returns an iterator to the end.
     */
        iterator end()
        {
            return iterator(this, _size);
        }
        const_iterator cend() const
        {
            return const_iterator(this, _size);
        }
        /**
     * checks whether the container is empty
     */
        bool empty() const
        {
            return _size == 0;
        }
        /**
     * returns the number of elements
     */
        size_t size() const
        {
            return _size;
        }
        /**
     * clears the contents
     */
        void clear()
        {
            _size = 0;
        }
        /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
        iterator insert(iterator pos, const T &value)
        {
            if (full())
                doublesize();
            for (int i = _size - 1; i >= pos.index; i--)
                store[i + 1] = store[i];
            _size++;
            store[pos.index] = new T(value); 
            return pos;
        }
        /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
        iterator insert(const size_t &ind, const T &value)
        {
            if (full())
                doublesize();
            if (ind > _size)
                throw index_out_of_bound();
            for (int i = _size - 1; i >= ind; i++)
                store[i + 1] = store[i];
            _size++;
            *(store[ind]) = new T(value);
            return iterator(this, ind);
        }
        /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
        iterator erase(iterator pos)
        {
            delete store[pos.index];

            for (int i = pos.index; i < _size - 1; i++)
                store[i] = store[i + 1];
            _size--;
            if (_size < (cap / 4))
                shrink();
            return pos;
        }
        /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
        iterator erase(const size_t &ind)
        {
            if (ind >= _size)
                throw index_out_of_bound();
            delete store[index];
            for (int i = ind; i < size - 1; i++)
                store[i] = store[i + 1];
            _size--;
            if (_size < (cap / 4))
                shrink();
            return iterator(this, ind);
        }
        /**
     * adds an element to the end.
     */
        void push_back(const T &value)
        {
            if (full())
                doublesize();
            insert(end(), value);
        }
        /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
        void pop_back()
        {
            if (_size == 0)
                throw container_is_empty();
            _size--;
            delete (store[_size]);
            if (_size < (cap / 4))
                shrink();
        }
    };
}

#endif