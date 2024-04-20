#ifndef _VECTOR
#define _VECTOR


// reservation, iterator
template<typename T>
class vector {
    unsigned int len;
    T* pData;

    //int reserved;

public:
    vector() : len(0), pData(new T[0]) {};
    vector(const vector& v){
        len = v.len;
        pData = new T[len];
        for(unsigned int i = 0; i < len; ++i)
            pData[i] = v.pData[i];
        std::cout << "gond";
    }
    ~vector(){ delete[] pData; };


    int size() const { return len; };

    void push_back(T new_element){
        T* new_pData = new T[len + 1];
        for(unsigned int  i = 0; i < len; ++i)
            new_pData[i] = pData[i];
        new_pData[len++] = new_element;
        delete[] pData;
        pData = new_pData;
    }

    T& operator[](unsigned int idx){
        return pData[idx];
    }

    T operator[](unsigned int idx) const {
        return pData[idx];
    }

    bool isEmpty(){
        return len == 0;
    }

    void clear() {
        len = 0;
        delete[] pData;
        pData = new T[len];
    }

    T pop(unsigned int idx) {
        if(idx < 0 || idx >= len) throw "vector: index error";
        T* new_pData = new T[len];
        for(unsigned int  i = 0; i < idx; ++i){
            new_pData[i] = pData[i];
        }
        T ret_v = pData[idx];
        for(unsigned int i = idx + 1; i < len; ++i){
            new_pData[i] = pData[i];
        }
        delete[] pData;
        pData = new_pData;
        --len;
        return ret_v;
    }

    void reserve(int reservation) {}

};

#endif // _VECTOR
