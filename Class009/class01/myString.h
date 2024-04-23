#ifndef __MYSTRING_H__
#define __MYSTRING_H__

namespace GJ
{
    class string
    {
    private:
        char *m_data_;
        int m_size_;

    public:
        string(const char* c_str = nullptr);
        string(const string &str);
        string(const string &&str);
        string &operator=(const string &str);
        string &operator=(const string &&str);
        char *c_str(void) const;
        ~string();
    }
}

#endif //__MYSTRING_H__