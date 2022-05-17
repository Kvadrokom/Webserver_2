#include <vector>
#include <string>
#include <iostream>

struct LocationData
{
    std::string path;
    std::string root;
    std::string method;
};

struct ServerParam
{
    int                         port;
    std::vector<LocationData>    location;
};

struct Parser_conf
{
    ServerParam*                servers;
    std::vector<std::string>    pars;
    size_t                      loc_size;
    size_t                      serv_size;
};

int main() 
{
  Parser_conf conf;
  conf.servers = new ServerParam[3];
  LocationData* loc = new LocationData[6];
  loc[0].root = "/www";
  loc[0].path = "/";
  loc[0].method = "GET";
  loc[1].root = "/www/images";
  loc[1].path = "/images/";
  loc[1].method = "POST";
  loc[2].root = "/www/images";
  loc[2].path = "/images/";
  loc[2].method = "HEAD";
  loc[3].root = "/www/images";
  loc[3].path = "SITE";
  loc[3].method = "PUT";
  loc[4].root = "www/hoop";
  loc[4].path = "DOCS";
  loc[4].method = "POST";
  loc[5].root = "SEWDER";
  loc[5].path = "FILES";
  loc[5].method = "POST";
  conf.servers[0].location.push_back(loc[0]);
  conf.servers[0].location.push_back(loc[1]);
  conf.servers[1].location.push_back(loc[2]);
  conf.servers[1].location.push_back(loc[3]);
  conf.servers[2].location.push_back(loc[4]);
  conf.servers[2].location.push_back(loc[5]);
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < conf.servers[i].location.size(); j++)
    {
      std::cout << conf.servers[i].location[j].root << " ";
      std::cout << conf.servers[i].location[j].method << " ";
      std::cout << conf.servers[i].location[j].path << " ";
      std::cout << "\n";
    }
    std::cout << "\n";
  }
  return 0;
}