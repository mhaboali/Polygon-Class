#include<iostream>
#include<math.h>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include <utility>
using namespace std;

// for profesional coders:
//---------------
typedef vector < pair<float, float> > v_float_pair;
typedef vector<float>vfloat;
#define all(v) ((v).begin(),(v).end())
#define sz(v) ((int)((v).size()))
					//------------------

//----------General functions------

vector<string> seprating(string);
float X_Float(string);
float Y_Float(string);
float Distance_bet_TwoPoints(pair<float, float>, pair<float, float>);
float Slope_Of_TwoPoints(pair<float, float>, pair<float, float>);
v_float_pair Make_Polygon(string);

//---------------------------------





class polygon
{
private:

	v_float_pair points;					//all points in polygon
	vector<float> x_coords;					//all x coordinates in polygon
	vector<float> y_coords;					//all y coordinates in polygon
	v_float_pair redunt_points;				//fake points
	v_float_pair points_without_redunt;		//critical points in polygon
	int size;								//number of polygon's points

public:
	polygon(string s)
	{
		//defentions:
		int pointer = 0;		int secondParameter = 0;		size = 0;
		int start = 0;			int end = 0;					int newstart = 0;


		for (int i = 0; i < s.length(); i++)
		{
			string xs = "";		string ys = "";
			if (s[i] == '(')
			{
		//for x coordinate:
				size++;
				start = i + 1;
				pointer = s.find(',', start);
				secondParameter = pointer - start;
				xs = s.substr(start, secondParameter);
				newstart = pointer + 1;

		//for y coordinate:

				end = s.find(')', newstart);
				secondParameter = end - newstart;
				ys = s.substr(newstart, secondParameter);
				//cout << "x===>" << xs << "  y===>" << ys << endl;

		// for whole point:

				float x =(float) atof(xs.c_str());
				float y = (float)atof(ys.c_str());
				//cout << "float x= " << x << " ,float y = " << y << endl;
				points.resize(size);
				points[size - 1] = make_pair(x, y);
				//cout << "(" << points[size - 1].first << "," << points[size - 1].second << ")";

		//for all x and y coords:
				x_coords.resize(size);
				x_coords[size - 1] = x;
				y_coords.resize(size);
				y_coords[size - 1] = y;

			}
		}
		//for points with redunat and without redundant:



	}
	vector<float> get_xCoords()
	{
		return x_coords;
	}
	vector<float> get_yCoords()
	{
		return y_coords;
	}
	int get_size()
	{
		return size;
	}
	void print_shape()
	{
		if (points_without_redunt.size() >= 3)
		{
			for (int i = 0; i < points_without_redunt.size(); i++)
			{
				cout << "(" << points_without_redunt[i].first << "," << points_without_redunt[i].second << ")";
				if (i != points_without_redunt.size() - 1)
					cout << ",";
			}
		}
		else
			cout << "it is not polygon.";
		cout << endl;
	}
	float Minimum_X()
	{
		sort(x_coords.begin(), x_coords.end());
		return x_coords[0];
	}
	float Minimum_Y()
	{
		sort(y_coords.begin(), y_coords.end());
		return y_coords[0];
	}
	float Maximum_X()
	{
		sort(x_coords.begin(), x_coords.end());
		return x_coords[size-1];
	}
	float Maximum_Y()
	{
		sort(y_coords.begin(), y_coords.end());
		return y_coords[size - 1];
	}
	v_float_pair Get_Redunt()
	{
		v_float_pair points_2 = points;

/////for the same points::


		for (int i = 0; i<points_2.size();i++)
		{
			for (int j = i+1; j<points_2.size();j++)
			{
				if (points_2[i].first == points_2[j].first&&points_2[i].second == points_2[j].second)
					{
						redunt_points.push_back(points_2[j]);
						points_2.erase(points_2.begin()+j);
						--j;
					}
			}
		}


/////for the same slopes::


		for (int m = 0; m < points_2.size(); m++)
		{
			if (m == points_2.size() - 2)
				continue;
			int second = m + 1;		int third = m + 2;		int j = m;

			for (second; second < points_2.size(); second++)
			{
				for (third; third < points.size(); third++)
				{
					//helping varibles::

					float x1, x2, x3, y1, y2, y3;
					x1 = points_2[m].first;		x2 = points_2[second].first;	x3 = points_2[third].first;
					y1 = points_2[m].second;	y2 = points_2[second].second;	y3 = points_2[third].second;
					float first_slope = (y2 - y1) / (x2 - x1);
					float second_slopoe = (y3 - y2) / (x3 - x2);

					// base condition:

					if ((first_slope == second_slopoe&&first_slope != 0) || (x1 == x2&&x2 == x3) || (y1 == y2&&y2 == y3))
					{
						redunt_points.push_back(points_2[second]);
						points_2.erase(points_2.begin() + second);
						--j;
						break;
					}
					else
						break;
				}

				break;
			}

		if (m == points_2.size() - 1)
			{
					int second = m;		int third = m  - 1;		int j = 0;

					//helping varibles::

						float x1, x2, x3, y1, y2, y3;
						x1 = points_2[j].first;		x2 = points_2[second].first;	x3 = points_2[third].first;
						y1 = points_2[j].second;	y2 = points_2[second].second;	y3 = points_2[third].second;
						float first_slope = (y2 - y1) / (x2 - x1);
						float second_slopoe = (y3 - y2) / (x3 - x2);

						// base condition:

						if ((first_slope == second_slopoe&&first_slope != 0) || (x1 == x2&&x2 == x3) || (y1 == y2&&y2 == y3))
						{
							redunt_points.push_back(points_2[second]);
							points_2.erase(points_2.begin() + second);
						}

			}
			if (m == points_2.size() - 1)
			{
				int second = 0;		int third =  1;		int j = m;

						//helping varibles::

						float x1, x2, x3, y1, y2, y3;
						x1 = points_2[j].first;		x2 = points_2[second].first;	x3 = points_2[third].first;
						y1 = points_2[j].second;	y2 = points_2[second].second;	y3 = points_2[third].second;
						float first_slope = (y2 - y1) / (x2 - x1);
						float second_slopoe = (y3 - y2) / (x3 - x2);

						// base condition:

						if ((first_slope == second_slopoe&&first_slope != 0) || (x1 == x2&&x2 == x3) || (y1 == y2&&y2 == y3))
						{
							redunt_points.push_back(points_2[second]);
							points_2.erase(points_2.begin() + second);

						}
			}



		}
		points_without_redunt = points_2;
		/*for (auto h : points_without_redunt)
			cout << "(" << h.first << "," << h.second << "),\n";
		cout << "\\\\\\\\" << endl<<endl;
		for (auto n : redunt_points)
			cout << "(" << n.first << "," << n.second << "),\n\n";
		*/
		return redunt_points;
	}
	int No_Of_Redunts()
	{
		return redunt_points.size();
	}
	v_float_pair Get_Critical_Points()
	{
		return points_without_redunt;
	}
	float Get_perimeter()
	{
		v_float_pair polyg;
		polyg = points_without_redunt;
		float perimeter = 0.0;
		for (int i = 0; i < polyg.size();i++)
		{
			if (i == polyg.size() - 1)
			{
				float dist = Distance_bet_TwoPoints(polyg[i], polyg[0]);
				perimeter = perimeter + dist;
			}
			else
			{
				float dist = Distance_bet_TwoPoints(polyg[i], polyg[i + 1]);
				perimeter = perimeter + dist;
			}
		}
		return perimeter;
	}
	bool Is_triangle()
	{
		v_float_pair polyg;
		polyg = points_without_redunt;
		if (polyg.size() == 3)
			return true;
		return false;
	}
	bool Is_rectangle()
	{
		v_float_pair polyg;
		polyg = points_without_redunt;
		if (polyg.size() == 4)
		{

			if (((polyg[0].first == polyg[1].first) && (polyg[2].first == polyg[3].first)
				&& (Distance_bet_TwoPoints(polyg[0], polyg[1]) == Distance_bet_TwoPoints(polyg[2], polyg[3]))) || ((polyg[0].second == polyg[1].second)
				&& (polyg[2].second == polyg[3].second) && (Distance_bet_TwoPoints(polyg[0], polyg[1]) == Distance_bet_TwoPoints(polyg[2], polyg[3]))))
				return true;
			else if ((Slope_Of_TwoPoints(polyg[0], polyg[1]) == Slope_Of_TwoPoints(polyg[2], polyg[3])
				&& (Distance_bet_TwoPoints(polyg[0], polyg[1]) == Distance_bet_TwoPoints(polyg[2], polyg[3])))
				|| (Slope_Of_TwoPoints(polyg[0], polyg[3]) == Slope_Of_TwoPoints(polyg[1], polyg[2])
				&& (Distance_bet_TwoPoints(polyg[0], polyg[3]) == Distance_bet_TwoPoints(polyg[1], polyg[2]))))
				return true;
				else
					return false;

		}
		else
			return false;
	}
	bool Is_trapezoide()
	{
		v_float_pair polyg;
		polyg = points_without_redunt;
		if (polyg.size() == 4)
		{
			if (((polyg[0].first == polyg[1].first) && (polyg[2].first == polyg[3].first)
				&& (Distance_bet_TwoPoints(polyg[0], polyg[1]) != Distance_bet_TwoPoints(polyg[2], polyg[3])))
				|| ((polyg[0].second == polyg[1].second) && (polyg[2].second == polyg[3].second)
				&& (Distance_bet_TwoPoints(polyg[0], polyg[1]) != Distance_bet_TwoPoints(polyg[2], polyg[3]))))
					return true;
			else if ((Slope_Of_TwoPoints(polyg[0], polyg[1]) == Slope_Of_TwoPoints(polyg[2], polyg[3])
				&& (Distance_bet_TwoPoints(polyg[0], polyg[1]) != Distance_bet_TwoPoints(polyg[2], polyg[3])))
				|| (Slope_Of_TwoPoints(polyg[0], polyg[3]) == Slope_Of_TwoPoints(polyg[1], polyg[2])
				&& (Distance_bet_TwoPoints(polyg[0], polyg[3]) != Distance_bet_TwoPoints(polyg[1], polyg[2]))))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	float Get_Area()
	{
		float area;		float s1 = 0, s2 = 0;
		for (int i = 0; i < points_without_redunt.size(); i++)
		{
			if (i == points_without_redunt.size() - 1)
			{
				s1 = s1+(points_without_redunt[i].first * points_without_redunt[0].second);
				s2 = s2+(points_without_redunt[i].second * points_without_redunt[0].first);
			}
			else
			{
				s1 = s1+(points_without_redunt[i].first * points_without_redunt[i + 1].second);
				s2 = s2+(points_without_redunt[i].second * points_without_redunt[i + 1].first);
			}
		}
		area = .5*(s1 - s2);
		return fabs(area);
	}
};


//----------General functions------

bool Is_Intersecting(polygon, polygon);
//---------------------------------

// for profesional coders:
//-----------------
typedef vector<polygon>vpolygon;
//----------------





vector<string> seprating(string Data)
{
	vector<string>vshapes;
	int left = 0;	int right = 0;
	for (int i = right; i < Data.size(); i++)
	{

		if (Data[i] == ';'||Data[i]==']')
		{
			right = i + 1;
			string polygon;		int here = (right-1) - left;
			polygon = Data.substr(left, here);

			left = right ;
			vshapes.push_back(polygon);
			//vshapes.push_back(";");

		}
	}
	return vshapes;
}
float Get_Max_x(vpolygon polys)
{
	int size = polys.size();
	float max = polys[0].Maximum_X();
	for (int i = 1; i < size; i++)
	{
		if (max < polys[i].Maximum_X())
			max = polys[i].Maximum_X();
	}
	return max;
}
float Get_Max_y(vpolygon polys)
{
	int size = polys.size();
	float max = polys[0].Maximum_Y();
	for (int i = 1; i < size; i++)
	{
		if (max < polys[i].Maximum_Y())
			max = polys[i].Maximum_Y();
	}
	return max;
}
float Get_Min_x(vpolygon polys)
{
	int size = polys.size();
	float min = polys[0].Minimum_X();
	for (int i = 1; i < size; i++)
	{
		if (min > polys[i].Minimum_X())
			min = polys[i].Minimum_X();
	}
	return min;
}
float Get_Min_y(vpolygon polys)
{
	int size = polys.size();
	float min = polys[0].Minimum_Y();
	for (int i = 1; i < size; i++)
	{
		if (min > polys[i].Minimum_Y())
			min = polys[i].Minimum_Y();
	}
	return min;
}
int Get_Total_no(vpolygon polys)
{
	int size = polys.size();
	int total = 0;
	for (int i = 0; i < size; i++)
	{
		total += polys[i].get_size();
	}
	return total;
}
int Total_No_Redunts(vpolygon polys)
{
	int total = 0;
	int No = 0;
	for (int i = 0; i < polys.size(); i++)
	{
		No = polys[i].No_Of_Redunts();
		total += No;
	}
	return total;
}
float X_Float(string s)
{
	int pointer = 0;		int secondParameter = 0;
	int start = 0;			int end = 0;
	float x;

	for (int i = 0; i < s.length(); i++)
	{
		string xs = "";
		if (s[i] == '(')
		{
			//for x coordinate:
			start = i + 1;
			pointer = s.find(',', start);
			secondParameter = pointer - start;
			xs = s.substr(start, secondParameter);

			// for whole point:

			 x = (float)atof(xs.c_str());
			 return x;
		}
	}
}
float Y_Float(string s)
{
	int pointer = 0;		int secondParameter = 0;
	int start = 0;			int end = 0;
	float y;

	for (int i = 0; i < s.length(); i++)
	{
		string ys = "";
		if (s[i] == ',')
		{
			//for y coordinate:
			start = i + 1;
			end = s.find(')', start);
			secondParameter = end - start;
			ys = s.substr(start, secondParameter);
			float y = (float)atof(ys.c_str());
			return y;
		}
	}

}
float Distance_bet_TwoPoints(pair<float, float>p1, pair<float, float>p2)
{
	float x1, x2, y1, y2,distance;
	x1 = p1.first;		x2 = p2.first;
	y1 = p1.second;		y2 = p2.second;
	return distance = sqrt((pow(x2 - x1, 2)) + (pow(y2 - y1, 2)));
}
float Slope_Of_TwoPoints(pair<float, float>p1, pair<float, float>p2)
{
	float x1, x2, y1, y2, slope;
	x1 = p1.first;		x2 = p2.first;
	y1 = p1.second;		y2 = p2.second;
	if (x1 != x2)
		return slope = (y2 - y1) / (x2 - x1);
	else
		exit;
}

v_float_pair Make_Polygon(string s)
{
	v_float_pair points = {};	int size;

	//defentions:
	int pointer = 0;		int secondParameter = 0;		size = 0;
	int start = 0;			int end = 0;					int newstart = 0;


	for (int i = 0; i < s.length(); i++)
	{
		string xs = "";		string ys = "";
		if (s[i] == '(')
		{
			//for x coordinate:
			size++;
			start = i + 1;
			pointer = s.find(',', start);
			secondParameter = pointer - start;
			xs = s.substr(start, secondParameter);
			newstart = pointer + 1;

			//for y coordinate:

			end = s.find(')', newstart);
			secondParameter = end - newstart;
			ys = s.substr(newstart, secondParameter);
			//cout << "x===>" << xs << "  y===>" << ys << endl;

			// for whole point:

			float x = (float)atof(xs.c_str());
			float y = (float)atof(ys.c_str());
			//cout << "float x= " << x << " ,float y = " << y << endl;
			points.resize(size);
			points[size - 1] = make_pair(x, y);
		}
	}
	return points;
}

bool Is_Intersecting(polygon p1, polygon p2)
{
	auto Points_poly1 = p1.Get_Critical_Points();
	auto Points_poly2 = p2.Get_Critical_Points();

	//----for sharing area &points&line----//

	float max_x1 = p1.Maximum_X();
	float max_y1 = p1.Maximum_Y();
	float min_x1 = p1.Minimum_X();
	float min_y1 = p1.Minimum_Y();
	float max_x2 = p2.Maximum_X();
	float max_y2 = p2.Maximum_Y();
	float min_x2 = p2.Minimum_X();
	float min_y2 = p2.Minimum_Y();
	int flag = 1;
	for (auto i : Points_poly1)
	{
		for (auto j : Points_poly2)
		{
			if ((i.first == j.first) && (i.second == j.second))
				return true;
			else if ((i.first > min_x2 && i.first<max_x2) && (i.second>min_y2 && i.second < max_y2))
				return true;
			else if ((j.first > min_x1 && j.first<max_x1) && (j.second>min_y1 && j.second < max_y1))
				return true;
			else
				flag=0;
		}

	}
	if (flag == 0)
		return false;

}


