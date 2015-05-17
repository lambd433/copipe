#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <list>
// #include <memory>
// #include "boost/date_time/gregorian/gregorian.hpp"

#ifndef CLIP_H
#define CLIP_H

//Linux
// const std::string set_cmd="xsel -bi";
// const std::string get_cmd="xsel -bo";

//Mac
const std::string get_cmd="pbcopy";
const std::string set_cmd="pbpaste";

//Windows

void setClip(std::string text);
std::string getClip();

class Clip
{
  // using greg = boost::gregorian;
  // using ClipData = greg:date;
  using ClipData = time_t;
  using ClipDate = std::string;
  using ClipHost = std::string;
 private:
  ClipData m_data;
  ClipDate m_date;
  ClipHost m_host;
  //  int m_kind;
 public:
 Clip(ClipData data, ClipDate date, ClipHost host): m_data(data), m_date(date), m_host(host){}
  ~Clip(){}
  ClipData getData(){return m_data;}
  ClipDate getDate(){return m_date;}
  ClipHost getHost(){return m_host;}
  void setData(){} 
  void setDate(){}
  void setHost(){}
};
class ClipBook
{
 public:
  std::list<Clip> m_clips;
};
#endif
