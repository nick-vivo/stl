#ifndef __HashTable_typeNode_OpenAddressing_Class__
#define __HashTable_typeNode_OpenAddressing_Class__

#include <string>

namespace HashTable
{
    namespace typeNode
    {
        template <class Tkey, class Tdata>
        class OpenAddressing
        {
        private:
            Tkey *key;
            Tdata *data;
            bool wasOccuped;

        public:
            OpenAddressing() : key(nullptr), data(nullptr), wasOccuped(false) {}

            OpenAddressing(const Tkey &key, const Tdata &data) : key(new Tkey(key)), data(new Tdata(data)), wasOccuped(true) {}

            void setKey(const Tkey &key) noexcept(false)
            {
                if (this->key)
                    *this->key = key;

                else
                    this->key = new Tkey(key);
            }

            void setData(const Tdata &data) noexcept(false)
            {
                if (this->data)
                    *this->data = data;

                else
                    this->data = new Tdata(data);
            }

            void setOccuped(const bool &occuped) noexcept
            {
                this->wasOccuped = occuped;
            }

            void set(const Tkey &key, const Tdata &data) noexcept(false)
            {
                setKey(key);
                setData(data);
            }

            Tkey *getKey() const noexcept
            {
                return key;
            }

            Tdata *getData() const noexcept
            {
                return data;
            }

            bool getOccuped() const noexcept
            {
                return this->wasOccuped;
            }

            bool nullKey() const noexcept
            {
                return !key;
            }

            bool nullData() const noexcept
            {
                return !data;
            }

            bool equalKey(const Tkey &key) const noexcept
            {
                return this->key && key == *this->key;
            }

            bool equalData(const Tdata &data) const noexcept
            {
                return this->data && data == *this->data;
            }

            std::string toString() const;

            ~OpenAddressing()
            {
                this->clear();
            }

            void clear() noexcept(false)
            {
                if (key)
                {
                    delete key;
                    key = nullptr;
                }

                if (data)
                {
                    delete data;
                    data = nullptr;
                }
            }
        };

        template <class Tkey, class Tdata>
        std::string OpenAddressing<Tkey, Tdata>::toString() const
        {
            Tkey *key = this->getKey();
            Tdata *data = this->getData();

            std::string result;

            result += ("key:");
            if (key)
                result += std::to_string(*key);
            result += (", data:");
            if (data)
                result += std::to_string(*data);

            result += (";");

            return result;
        }
    }
}
#endif