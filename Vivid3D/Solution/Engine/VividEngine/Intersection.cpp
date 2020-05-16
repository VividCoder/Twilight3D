#include "pch.h"
#include "Intersection.h"

using namespace Vivid::Intersections;
using namespace Vivid::Maths;

bool Vivid::Intersections::Intersection::RayToTri(float3 origin, float3 vec, float3 vertex0, float3 vertex1, float3 vertex2, float3& out)
{

    const float EPSILON = 0.0000001;
    //Vector3D vertex0 = inTriangle->vertex0;
    //Vector3D vertex1 = inTriangle->vertex1;
    //Vector3D vertex2 = inTriangle->vertex2;
    float3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    
    h = MathsUtil::CrossProduct(vec,edge2);
    a = MathsUtil::DotProduct(edge1,h);

    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0 / a;
    s = origin - vertex0;
    u = f * MathsUtil::DotProduct(s,h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = MathsUtil::CrossProduct(s,edge1);

    v = f * MathsUtil::DotProduct(vec,q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * MathsUtil::DotProduct(edge2,q);
    if (t > EPSILON) // ray intersection
    {
        out = origin + vec * t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;

	return false;
}