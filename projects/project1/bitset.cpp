#include "bitset.hpp"

Bitset::Bitset() {
    valid_bit_set = new uint8_t[1]();
    bit_set_size=8;
}

Bitset::Bitset(intmax_t size){
    if(size<=0){
        valid=false;
        valid_bit_set=nullptr;
    }
    else{
        valid=true;
        bit_set_size=size;
        valid_bit_set = new uint8_t[size]();
    }
}

Bitset::Bitset(const std::string & value) {
    for(char check:value){
        if(check!='0' && check!='1'){
            valid=false;
            return;
        }
    }
    valid=true;
    bit_set_size=value.length();
    valid_bit_set= new uint8_t[bit_set_size]();
    for(size_t i=0;i<bit_set_size;i++){
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
    return bit_set_size;
};
bool Bitset::good() const{
    return valid;
};
void Bitset::set(intmax_t index){
    if(index>0&&static_cast<size_t>(index)<size()){
        valid_bit_set[index]=1;
    }
    else{
        valid=false;
    }
}
void Bitset::reset(intmax_t index){
    if(index>0&&static_cast<size_t>(index)<size()){
        valid_bit_set[index]=0;
    }
    else{
        valid=false;
    }
};
void Bitset::toggle(intmax_t index){
    if (index >= 0 && static_cast<size_t>(index) < size()) {
        if(valid_bit_set[index]==0){
            valid_bit_set[index]=1;
        }
        else if(valid_bit_set[index]==1){
            valid_bit_set[index]=0;
        }
    } else {
        valid = false;
    }
};
bool Bitset::test(intmax_t index){
    if(index>=0&&static_cast<size_t>(index)<size()){
        if(valid_bit_set[index]==1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        valid=false;
        return false;
    }
};
std::string Bitset::asString() const{
    std::string bit_set_string="";

    if(!valid){
        bit_set_string='0';
    }
    else{for(int i = bit_set_size-1;i>=0;i){
        if(valid_bit_set[i]==0){
            bit_set_string+='0';
        }
        else if(valid_bit_set[i]==1){
            bit_set_string+='1';
        }
    }}
    return bit_set_string;
};


