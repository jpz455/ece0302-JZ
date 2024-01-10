#include "bitset.hpp"

Bitset::Bitset() {
    valid_bit_set = new uint8_t[1]();
}

Bitset::Bitset(intmax_t size){
    if(size<=0){
        !valid;
        valid_bit_set=nullptr;
    }
    else{
        valid=true;
        size_t N = (size + 7) / 8;
        valid_bit_set = new uint8_t[N]();
    }
}

Bitset::Bitset(const std::string & value) {
    for(char check:value){
        if(check=!0 && check!=1){
            !valid;
            return;
        }
    }
    valid=true;
    size_t N=value.length();
    N=std::ceil(N)/8;
    valid_bit_set= new uint8_t[N]();
    for(size_t i=0;i<N;i++){
        if(value[i]=='1'){
            valid_bit_set[i]=1;
        }
        else{
            valid_bit_set[i]=0;
        }
    }

}

Bitset::~Bitset() {
    delete [] valid_bit_set;
}

intmax_t Bitset::size()const {
    return sizeof(valid_bit_set);
};
bool Bitset::good() const{};
void Bitset::set(intmax_t index){};
void Bitset::reset(intmax_t index){};
void Bitset::toggle(intmax_t index){};
bool Bitset::test(intmax_t index){};
std::string Bitset::asString() const{};


