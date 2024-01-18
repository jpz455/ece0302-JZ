#include "bitset.hpp"

Bitset::Bitset() {
    bit_set_size=8;
    valid_bit_set = new bool[bit_set_size];
    valid=true;
    for(int i=0;i<bit_set_size;i++){
        *(valid_bit_set+i)=0;
    }
};

Bitset::Bitset(intmax_t size){
   if(size>0){
    valid=true;
   }
   else{
    valid=false;
   }
   if(valid){
   bit_set_size=size;
   valid_bit_set = new bool[bit_set_size];
   for(int i=0;i<bit_set_size;i++){
    *(valid_bit_set+i)=0;
   }
   }
   if(!valid){
    valid_bit_set=nullptr;
   }
};

Bitset::Bitset(const std::string & value) {
    bit_set_size=value.length();
    valid_bit_set= new bool[bit_set_size];
    valid=true;
    for(int i=0;i<bit_set_size;i++){
        if(value[i]!='0'&&value[i]!='1'){
            valid=false;
        }
        else if(value[i]=='1'){
            valid_bit_set[i]=1;
        }
        else{
            valid_bit_set[i]=0;
        }
        
    }
};

Bitset::~Bitset() {
    delete [] valid_bit_set;
};

intmax_t Bitset::size()const {
    return bit_set_size;
};

bool Bitset::good() const{
    return valid;
};

void Bitset::set(intmax_t index){
    if(index>=0&&index<bit_set_size){
        *(valid_bit_set+index)=1;
        valid=true;
    }
    else{
        valid=false;
    }
};

void Bitset::reset(intmax_t index){
    if(index>=0&&index<bit_set_size){
        *(valid_bit_set+index)=0;
        valid=true;
    }
    else{
        valid=false;
    }
};

void Bitset::toggle(intmax_t index){
    if (index >= 0 && index<bit_set_size){
        if(*(valid_bit_set+index)==0){
           *(valid_bit_set+index)=1;
           valid=true;
        }
        else if(*(valid_bit_set+index)==1){
           *(valid_bit_set+index)=0;
           valid=true;
        }
    } 
    else {
        valid = false;
    }
};

bool Bitset::test(intmax_t index){
    if(index>=0 && index<bit_set_size){
        if(*(valid_bit_set+index)==1){
            valid=true;
            return true;
        }
    }
    else{
        valid=false;
        return false;
    }
};

std::string Bitset::asString() const{
    std::string returnBitset="";
    for(int i=0;i<bit_set_size;i++){
        std::string temp;
        if(*(valid_bit_set+i)==0){
            temp='0';
        }
        else{
            temp='1';
        }
        returnBitset+=temp;
    }
 return returnBitset;
};


