#ifndef __PLANE__
#define __PLANE__

#include "math.h"

static const float Epsilon = 1.0e-05f;

struct plane_t
{
   plane_t() {
      d = 0;
   }

   virtual ~plane_t()                  { }
   
   void Reset(void) {
      n.Set(0, 0, 0); d = 0;
   }

   bool IsFront(vec3_t &pt) {
      return (GetPointDistance(pt) > 0.0f) ? 1 : 0;
   }

   bool IsBack(vec3_t &pt) {
      return !(IsFront(pt));
   }

   inline bool IsOn(vec3_t &pt);   

   inline void CalcPlane(vec3_t &pta, vec3_t &ptb, vec3_t &ptc);
 
   inline bool LineIntersect(vec3_t &start, vec3_t &end, vec3_t &point,
    vec3_t &result);

  
   float GetPointDistance(vec3_t &pt)  {
      return n.Dot(pt) + d;
   } 

   const vec3_t &GetNormal(void)  {
      return n;
   }
   
   const float &GetD(void){
      return d;
   }

protected:
   vec3_t n;
   float d;
};

inline bool plane_t::IsOn(vec3_t &pt)
{
   float d = GetPointDistance(pt);
   return (d > -Epsilon && d < Epsilon) ? 1 : 0;
}

inline void plane_t::CalcPlane(vec3_t &pta, vec3_t &ptb, vec3_t &ptc)
{
   n.Cross(ptb - pta, ptc - pta);
   n.Normalize();
   d = -ptc.Dot(n);
}

inline bool plane_t::LineIntersect(vec3_t &start, vec3_t &end, vec3_t &point,
 vec3_t &result)
{
	float denom, numer, u;
	vec3_t dir;

	dir = end - start;

	denom = n.Dot(dir);

	if (denom > -Epsilon && denom < Epsilon)
		return 0; 

	numer = n.Dot(point - start);

	u = numer / denom;

	if (u <= 0.0f || u > 1.0f)
		return 0;

	result = start + dir * u; 
	return 1;
}

#endif