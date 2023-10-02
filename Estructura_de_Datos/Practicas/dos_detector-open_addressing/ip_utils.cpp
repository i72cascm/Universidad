/**
 * @file ip_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <algorithm>
#include "ip_utils.hpp"

std::uint64_t
IpToInt::operator() (const IP& ip) const
{
    std::uint64_t ret_val = 0l;
    //TODO (done)
    //Remember: casting to 64 bits unsigned integer to do not loss bits.
    //Hint: mult by 2^n means shift to left n bits.
    uint64_t aux = (static_cast<uint64_t>(ip.bytes[0])<<24)+(static_cast<uint64_t>(ip.bytes[1])<<16)+(static_cast<uint64_t>(ip.bytes[2])<<8)+(static_cast<uint64_t>(ip.bytes[3]));
    return (aux);
    //
    return ret_val;
}

std::ostream&
operator<< (std::ostream& out, const IP& ip)
{
    //TODO (done)
    //Remember: we want to output the ascii code, not the char.
    out<<static_cast<int>(ip.bytes[0])<<'.'<<static_cast<int>(ip.bytes[1])<<'.'<<static_cast<int>(ip.bytes[2])<<'.'<<static_cast<int>(ip.bytes[3]);
    //
    return out;
}

std::istream&
operator>>(std::istream& in, IP& ip) noexcept(false)
{
    //TODO (done)
    //Hint: you can use a std::istringstream to convert from text to uint8_t.
    //Hint: you can use the std::replace algorithm to replace '.' by ' '.
    //Remember: if a wrong format is detected, throw an runtime_error exception.
    std::string strIP;
    in >> strIP;
    int aux[4];

    if(in){
        for(size_t i = 0;i < strIP.size();++i){
            if (strIP[i]=='.'){
                strIP[i]=' ';
            }
                
        }

        std::istringstream input(strIP);
        input >> aux[0] >> aux[1] >> aux[2] >> aux[3];

        if (input){
            
            ip.bytes[1] = static_cast<uint8_t>(aux[1]);
            ip.bytes[2] = static_cast<uint8_t>(aux[2]);
            ip.bytes[3] = static_cast<uint8_t>(aux[3]);
            ip.bytes[0] = static_cast<uint8_t>(aux[0]);
        }

        if ( aux[1] > 255 || aux[3] >255 || aux[2] > 255 || aux[0] >255 ){
            throw std::runtime_error("Invalid IP address");
        }
        
    }
    //
    return in;
}

IpToInt::Ref
IpToInt::create()
{
    return std::make_shared<IpToInt>();
}
