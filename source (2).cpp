
#include<C:\Users\Abo 3li\Documents\Visual Studio 2013\Projects\the project 2\the project\classes_funcs.h>





//----Level One-----
int Get_Total_no(vpolygon);
float Get_Max_x(vpolygon);
float Get_Max_y(vpolygon);
float Get_Min_x(vpolygon);
float Get_Min_y(vpolygon);
int Total_No_Redunts(vpolygon);
//------------------------------------
//(1.124, 5.56), (3.3, 4), (6, 4); (6.25, 12.17), (3, 12)

int main()
{
		string input, Data,Operation;
		//getline(cin, input);
		input = R"(Polygons=[
(4,8),(4,3),(4,3),(10,3),(13,3),(13,8),(13,8);
(-1,5),(-4,11),(2,18),(2,18),(2,18),(8,6);
(17,14),(9,9),(14,5),(17,14);
(-13,-1),(-6,3),(2,-11),(-5,-15),(-9,-8),(-9,-8);
(7,-14),(4,-17),(4,-17),(-1,-14),(-2,-9),(3,-6),(10,-7),(6,-11);
(-7,12),(-6.5,13),(3,4),(3,4),(-8,10);
(19,-8),(19,-8),(16,-3),(10,-4),(7,-8),(10,-11),(13,-8),(14,-12),(19,-8),(19,-8);
(7,-4),(5,-5),(3,-6),(5,-1);
(3,-6),(1,-2),(-1,-4)])";


		int size_of_string = input.size() - 1;
		Data = input.substr(10, size_of_string);


	//creating object of polygon:

		auto vpoly = seprating(Data);
		vpolygon shapes;
		for (int i = 0; i < (int)vpoly.size(); i++)
		{
			shapes.push_back(polygon(vpoly[i]));
			//shapes[i].print_shape();
			shapes[i].Get_Redunt();
		}

	//here start operations:

		while (cin >> Operation)
		{
			if (Operation == "Quit")	break;

			if (Operation == "Number_Polygons")			{ cout << shapes.size() << endl; }

			if (Operation == "Total_Number_Points")		{ cout << Get_Total_no(shapes) << endl; }

			if (Operation == "Minimum_X")				{ cout << Get_Min_x(shapes) << endl; }

			if (Operation == "Maximum_X")				{ cout << Get_Max_x(shapes) << endl; }

			if (Operation == "Minimum_Y")				{ cout << Get_Min_y(shapes) << endl; }

			if (Operation == "Maximum_Y")				{ cout << Get_Max_y(shapes) << endl; }

			if (Operation == "Enclosing_Rectangle")
			{
				cout << "(" << Get_Min_x(shapes) << "," << Get_Min_y(shapes) << "),";
				cout << "(" << Get_Max_x(shapes) << "," << Get_Min_y(shapes) << "),";
				cout << "(" << Get_Max_x(shapes) << "," << Get_Max_y(shapes) << "),";
				cout << "(" << Get_Min_x(shapes) << "," << Get_Max_y(shapes) << ")";
				cout << endl;
			}

			if (Operation == "Total_Redundant_Points")	{ cout << Total_No_Redunts(shapes) << endl; }
			////////------end of level one el7------////



			////-------- second level-----///


			if (Operation == "Polygon_Points")
			{
				int order_of_polygon;
				cin >> order_of_polygon;
				if (order_of_polygon <= shapes.size())
					shapes[order_of_polygon-1].print_shape();
				
			}

			if (Operation == "Point_Polygons")
			{
				string point;
				cin >> point;
				float x = X_Float(point);
				float y = Y_Float(point);
				vfloat All_x;
				vfloat All_y;
				vector<int> Ids;
				for (int i = 0; i < shapes.size(); i++)
				{
					All_x = shapes[i].get_xCoords();
					All_y = shapes[i].get_yCoords();
					for (int j = 0; j < All_x.size(); j++)
						if (x == All_x[j] && y == All_y[j])
						{
							Ids.push_back(i + 1);
							break;
						}
				}
				if (Ids.size()>0)
				{
					for (int i = 0; i < Ids.size(); i++)
					{
						cout << Ids[i];
						if ((i != Ids.size() - 1))
							cout << ",";
					}
				}
				else
					cout << "none";
				cout << endl;
			}

			if (Operation == "List_Polygons_Points")
			{
				string specifier;  int num_points;
				vector<int>Ids_More,Ids_Less,Ids_Equal;
				cin >> specifier >> num_points;
				if (specifier == "More")
				{
					for (int i = 0; i < shapes.size(); i++)
					{
						v_float_pair real_points = shapes[i].Get_Critical_Points();
						if (num_points < real_points.size())
							Ids_More.push_back(i + 1);

					}
					if (Ids_More.size() > 0)
					{
						for (int i = 0; i < Ids_More.size(); i++)
						{
							cout << Ids_More[i];
							if ((i != Ids_More.size() - 1))
								cout << ",";
						}
					}
					else
						cout << "none";
					cout << endl;
				}
					else if (specifier == "Less")
					{
						for (int i = 0; i < shapes.size(); i++)
						{
							v_float_pair real_points = shapes[i].Get_Critical_Points();
							if (num_points>real_points.size())
								Ids_Less.push_back(i + 1);
						}
						if (Ids_Less.size()>0)
						{
							for (int i = 0; i < Ids_Less.size(); i++)
							{
								cout << Ids_Less[i];
								if ((i != Ids_Less.size() - 1))
									cout << ",";
							}
						}
						else
							cout << "none";
						cout << endl;
					}

					else if (specifier == "Equal")
					{
						for (int i = 0; i < shapes.size(); i++)
						{
							v_float_pair real_points = shapes[i].Get_Critical_Points();
							if (num_points == real_points.size())
								Ids_Equal.push_back(i + 1);
						}
						if (Ids_Equal.size()>0)
						{
							for (int i = 0; i < Ids_Equal.size(); i++)
							{
								cout << Ids_Equal[i];
								if ((i != Ids_Equal.size() - 1))
									cout << ",";
							}
						}
						else
							cout << "none";
						cout << endl;
					}
				}


			if (Operation == "List_Points_Polygons")
			{
				string specifier;
				int num_polygons;
				v_float_pair points_more, points_less, points_equal;



				cin >> specifier >> num_polygons;

				for (int i = 0; i < shapes.size() - 1; i++)
				{

					auto first_polygon = shapes[i].Get_Critical_Points();
					for (int j = 0; j < first_polygon.size(); j++)
					{
						int counter = 1;
						for (int m = i + 1; m < shapes.size(); m++)
						{
							auto another_polygon = shapes[m].Get_Critical_Points();

							for (int k = 0; k<another_polygon.size(); k++)
							{
								if (first_polygon[j] == another_polygon[k])
								{
									counter++;
									break;
								}
							}
						}
						if (counter>num_polygons)
							points_more.push_back(first_polygon[j]);
						else if (counter < num_polygons&&counter != 1)
							points_less.push_back(first_polygon[j]);
						else if (counter == num_polygons)
							points_equal.push_back(first_polygon[j]);
					}
				}
				if (specifier == "More")
				{
					if (points_more.empty())
						cout << "none" << endl;
			
					for (auto i : points_more)
						cout << "(" << i.first << "," << i.second << ")" << endl;
				}

				if (specifier == "Less")
				{
					if (points_less.empty())	
						cout << "none" << endl;
						
					for (auto i : points_less)
						cout << "(" << i.first << "," << i.second << ")" << endl;

				}
				if (specifier == "Equal")
				{
					if (points_equal.empty())
						cout << "none" << endl;
						
					for (auto i : points_equal)
						cout << "(" << i.first << "," << i.second << ")" << endl;
				}
			}


			if (Operation == "Polygon_Perimeter")
			{
				int num_of_polygon;		cin >> num_of_polygon;
				if (num_of_polygon <= shapes.size())
					cout << shapes[num_of_polygon - 1].Get_perimeter() << endl;
			}


			if (Operation == "List_Triangles")
			{
				vector<int>Ids;
				for (int i = 0; i < shapes.size(); i++)
					if (shapes[i].Is_triangle())
						Ids.push_back(i + 1);
				for (int i = 0; i < Ids.size(); i++)
				{
					cout << Ids[i];
					if ((i != Ids.size()-1) )
						cout << ",";
				}
				cout << endl;
			}


			if (Operation == "List_Rectangles")
			{
				vector<int>Ids;
				for (int i = 0; i < shapes.size(); i++)
					if (shapes[i].Is_rectangle())
						Ids.push_back(i + 1);
				for (int i = 0; i < Ids.size(); i++)
				{
					cout << Ids[i];
					if ((i != Ids.size() - 1))
						cout << ",";
				}
				cout << endl;
			}

			if (Operation == "List_Trapezoid")
			{
				vector<int>Ids;
				for (int i = 0; i < shapes.size(); i++)
					if (shapes[i].Is_trapezoide())
						Ids.push_back(i + 1);
				for (int i = 0; i < Ids.size(); i++)
				{
					cout << Ids[i];
					if ((i != Ids.size() - 1))
						cout << ",";
				}
				cout << endl;
			}



			//----------End of level 2 el7-------------//

			//--------------Level Three----------//


			if (Operation == "Inside_Rectangle")
			{
				string points;
				getline(cin, points);

				//----for given polygon----//
				v_float_pair polygon = Make_Polygon(points);
				float min_x, max_x, min_y, max_y;
				max_x = min_x = polygon[0].first;
				max_y = min_y = polygon[0].second;
				for (int i = 1; i < polygon.size(); i++)
				{
					if (polygon[i].first < min_x)
						min_x = polygon[i].first;
					if (polygon[i].first > max_x)
						max_x = polygon[i].first;
					if (polygon[i].second < min_y)
						min_y = polygon[i].second;
					if (polygon[i].second > max_y)
						max_y = polygon[i].second;
				}

				//----for The Ids------//
				vector<int> Ids;
				for (int i = 0; i < shapes.size(); i++)
				{
					float X_max = shapes[i].Maximum_X();
					float X_min = shapes[i].Minimum_X();
					float Y_max = shapes[i].Maximum_Y();
					float Y_min = shapes[i].Minimum_Y();
					if (((X_max<max_x) && (X_max>min_x) && (X_min<max_x) && (X_min>min_x)) && ((Y_max<max_y) && (Y_max>min_y) && (Y_min<max_y) && (Y_min>min_y)))
							Ids.push_back(i+1);
				}
				if (Ids.empty())
					cout << "none" << endl;
				else
					for (int i = 0; i < Ids.size(); i++)
					{
						cout << Ids[i];
						if ((i != Ids.size() - 1))
							cout << ",";
					}
			}



			if (Operation == "Polygons_Enclosing_Point")
			{
				string center;		getline(cin, center);
				float x, y;

				//for center//

				//defentions:	
				int pointer = 0;		int secondParameter = 0;
				int start = 0;			int end = 0;					int newstart = 0;

				for (int i = 0; i < center.length(); i++)
				{
					string xs = "";		string ys = "";
					if (center[i] == '(')
					{
						//for x coordinate:		
						start = i + 1;
						pointer = center.find(',', start);
						secondParameter = pointer - start;
						xs = center.substr(start, secondParameter);
						newstart = pointer + 1;

						//for y coordinate:

						end = center.find(')', newstart);
						secondParameter = end - newstart;
						ys = center.substr(newstart, secondParameter);

						// for whole point:

						x = (float)atof(xs.c_str());
						y = (float)atof(ys.c_str());
					}
				}

					//----for The Ids------//Polygons_Enclosing_Point
					vector<int> Ids;
					for (int i = 0; i < shapes.size(); i++)
					{
						vfloat Xs = shapes[i].get_xCoords(), Ys=shapes[i].get_yCoords();
						float X_max = shapes[i].Maximum_X();
						float X_min = shapes[i].Minimum_X();
						float Y_max = shapes[i].Maximum_Y();
						float Y_min = shapes[i].Minimum_Y();
						if (X_max>=x &&  X_min<=x && Y_max>=y &&  Y_min<=y)
								Ids.push_back(i+1);
					}
					
					if (Ids.empty())
						cout << "none" << endl;
					else
						for (int i = 0; i < Ids.size(); i++)
						{
							cout << Ids[i];
							if ((i != Ids.size() - 1))
								cout << ",";
						}
					cout << endl;
				}

				if (Operation == "Inside_Circle")
				{

					string center;		getline(cin, center);
					float radius;		
				float x_center, y_center;

				//for center//

				//defentions:	
				int pointer = 0;		int secondParameter = 0;
				int start = 0;			int end = 0;					int newstart = 0;

				for (int i = 0; i < center.length(); i++)
				{
					string xs = "";		string ys = "";			string rad;
					if (center[i] == ')')
					{
						rad = center.substr(i + 2);
						radius = atof(rad.c_str());
					}
					if (center[i] == '(')
					{
						//for x coordinate:		
						start = i + 1;
						pointer = center.find(',', start);
						secondParameter = pointer - start;
						xs = center.substr(start, secondParameter);
						newstart = pointer + 1;

						//for y coordinate:

						end = center.find(')', newstart);
						secondParameter = end - newstart;
						ys = center.substr(newstart, secondParameter);

						// for whole point:

						x_center = (float)atof(xs.c_str());
						y_center = (float)atof(ys.c_str());
					}
				}
				float min_x, max_x, min_y, max_y;
				min_x = x_center - radius;
				max_x = x_center + radius;
				min_y = y_center - radius;
				max_y = y_center + radius;

				//----for The Ids------//
				vector<int> Ids;
				for (int i = 0; i < shapes.size(); i++)
				{
					float X_max = shapes[i].Maximum_X();
					float X_min = shapes[i].Minimum_X();
					float Y_max = shapes[i].Maximum_Y();
					float Y_min = shapes[i].Minimum_Y();
					if (X_max<=max_x && X_max>=min_x && X_min<=max_x && X_min>=min_x)
						if (Y_max<=max_y && Y_max>=min_y && Y_min<=max_y && Y_min>=min_y)
							Ids.push_back(i);
				}
				if (Ids.empty())
					cout << "none" << endl;
				else
					for (int i = 0; i < Ids.size(); i++)
					{
						cout << Ids[i];
						if ((i != Ids.size() - 1))
							cout << ",";
					}
			}


				if (Operation == "Is_Intersecting")
				{
					int polygon1, polygon2;		char ch;
					cin >> polygon1 >>ch>> polygon2;
					int indx1 = polygon1 - 1;		int indx2 = polygon2 - 1;
					if (indx1>shapes.size() && indx2 > shapes.size())
						break;
					v_float_pair Points_poly1 = shapes[indx1].Get_Critical_Points();
					v_float_pair Points_poly2 = shapes[indx2].Get_Critical_Points();
								
							//----for sharing area &points&line----//

					float max_x1 = shapes[indx1].Maximum_X();
					float max_y1 = shapes[indx1].Maximum_Y();
					float min_x1 = shapes[indx1].Minimum_X();
					float min_y1 = shapes[indx1].Minimum_Y();
					float max_x2 = shapes[indx2].Maximum_X();
					float max_y2 = shapes[indx2].Maximum_Y();
					float min_x2 = shapes[indx2].Minimum_X();
					float min_y2 = shapes[indx2].Minimum_Y();
					int flag = 0;
					for (auto i : Points_poly1)
					{
						for (auto j : Points_poly2)
						{
							if ((i.first == j.first) && (i.second == j.second))
							{
								flag = 1;
								break;
							}
							else if ((i.first > min_x2 && i.first<max_x2) && (i.second>min_y2 && i.second < max_y2))
							{
								flag = 1;
								break;
							}
							else if ((j.first > min_x1 && j.first<max_x1) && (j.second>min_y1 && j.second < max_y1))
							{
								flag = 1;
								break;
							}
						}
						if (flag == 1)
							break;							
					}
					if (flag == 1)
						cout << "TRUE\n";
					else
						cout << "FALSE\n";

				}

				if (Operation == "Intersecting_Group")
				{
					int polygon1, polygon2, polygon3;	char ch1, ch2;
					cin >> polygon1 >>ch1>> polygon2>>ch2>>polygon3;
					int indx1 = polygon1 - 1;		int indx2 = polygon2 - 1;		int indx3 = polygon3 - 1;
					auto Points_poly1 = shapes[indx1].Get_Critical_Points();
					auto Points_poly2 = shapes[indx2].Get_Critical_Points();
					auto Points_poly3 = shapes[indx3].Get_Critical_Points();

					//----for sharing area &points&line----//

					float max_x1 = shapes[indx1].Maximum_X();
					float max_y1 = shapes[indx1].Maximum_Y();
					float min_x1 = shapes[indx1].Minimum_X();
					float min_y1 = shapes[indx1].Minimum_Y();
					float max_x2 = shapes[indx2].Maximum_X();
					float max_y2 = shapes[indx2].Maximum_Y();
					float min_x2 = shapes[indx2].Minimum_X();
					float min_y2 = shapes[indx2].Minimum_Y();
					float max_x3 = shapes[indx3].Maximum_X();
					float max_y3 = shapes[indx3].Maximum_Y();
					float min_x3 = shapes[indx3].Minimum_X();
					float min_y3 = shapes[indx3].Minimum_Y();

					int flag = 0;
					for (auto i : Points_poly1)
					{
						for (auto j : Points_poly2)
						{
							if ((i.first == j.first) && (i.second == j.second))
							{
								flag = 1;
								break;
							}
							else if ((i.first > min_x2 && i.first<max_x2) && (i.second>min_y2 && i.second < max_y2))
							{
								flag = 1;
								break;
							}
							else if ((j.first > min_x1 && j.first<max_x1) && (j.second>min_y1 && j.second < max_y1))
							{
								flag = 1;
								break;
							}
						}
						if (flag == 1)
							break;
					}
					if (flag == 1)
						flag = 0;
					
					for (auto i : Points_poly1)
					{
						if (flag == 0)
							break;
						for (auto j : Points_poly3)
						{
							if ((i.first == j.first) && (i.second == j.second))
							{
								flag = 1;
								break;
							}
							else if ((i.first > min_x3 && i.first<max_x3) && (i.second>min_y3 && i.second < max_y3))
							{
								flag = 1;
								break;
							}
							else if ((j.first > min_x1 && j.first<max_x1) && (j.second>min_y1 && j.second < max_y1))
							{
								flag = 1;
								break;
							}
						}
						if (flag == 1)
							break;
					}
					if (flag == 1)
						flag = 0;
					
						
					for (auto i : Points_poly2)
					{
						if (flag == 0)
							break;
						for (auto j : Points_poly3)
						{
							if ((i.first == j.first) && (i.second == j.second))
							{
								flag = 1;
								break;
							}
							else if ((i.first > min_x2 && i.first<max_x2) && (i.second>min_y2 && i.second < max_y2))
							{
								flag = 1;
								break;
							}
							else if ((j.first > min_x1 && j.first<max_x1) && (j.second>min_y1 && j.second < max_y1))
							{
								flag = 1;
								break;
							}
						}
						if (flag == 1)
							break;
					}

					if (flag == 1)
						cout << "TRUE\n";
					else
						cout << "FALSE\n";
				}

				if (Operation == "Polygon_Area")
				{
					int no_polygon;		cin >> no_polygon;
					int order = no_polygon - 1;
					cout << shapes[order].Get_Area()<<endl;
				}

				if (Operation == "Polygons_Area_Range")
				{
					float minA, maxA;		char ch;
					cin >> minA >>ch>> maxA;
					vector<int>Ids;
					for (int i = 0; i < shapes.size(); i++)
					{
						float area = shapes[i].Get_Area();
						if (area>minA&&area < maxA)
							Ids.push_back(i + 1);
					}
					for (int i = 0; i < Ids.size(); i++)
					{
						cout << Ids[i];
						if ((i != Ids.size() - 1))
							cout << ",";
					}
					cout << endl;
				}
				
				if (Operation == "Largest_Intersecting_Pair")
				{
					pair<int, int> IDS;
					float max_sum_area=0;
					for (int i = 0; i < shapes.size(); i++)
					{
						for (int j = i + 1; j < shapes.size()-1; j++)
						{
							if (Is_Intersecting(shapes[i], shapes[j]))
							{
								float sum_area = shapes[i].Get_Area() + shapes[j].Get_Area();
								if (sum_area > max_sum_area)
									IDS = make_pair(i, j);
							}
						}
					}
					cout << IDS.first << "," << IDS.second << endl;
				}
	//---------el7 the end of level 3-------//

	//---------level el bouns---------------//

				if (Operation == "Is_Connected")
				{
					int poly1, poly2;		char ch;
					cin >> poly1 >> ch >> poly2;
					int indx1 = poly1 - 1, indx2 = poly2 - 1;
					vector<int>Ids1, Ids2;
					if (Is_Intersecting(shapes[indx1], shapes[indx2]))
					{
						Ids1.push_back(indx1 + 1);		Ids1.push_back(indx2 + 1);
						Ids2.push_back(indx1 + 1);		Ids2.push_back(indx2 + 1);
					}
					for (int i = 0; i < shapes.size(); i++)
					{
						if (i == indx1 || i == indx2)
							continue;
						if (Is_Intersecting(shapes[i], shapes[indx1]))
							Ids1.push_back(i + 1);
						if (Is_Intersecting(shapes[i], shapes[indx2]))
							Ids2.push_back(i + 1);
					}
					if (Ids1.empty() || Ids2.empty())
						cout << "FALSE\n";
					else
					{
						int flag = 0;
						for (auto i : Ids1)
						{
							for (auto j : Ids2)
							{
								if (i == j)
								{
									flag = 1;
									break;
								}
							}
							if (flag == 1)
								break;
						}
						if (flag == 1)
							cout << "TRUE\n";
						else
							cout << "FALSE\n";
					}
				}

				if (Operation == "Is_Connected_Group")
				{
					int poly1, poly2, poly3;		char ch1, ch2;
					cin >> poly1 >> ch1 >> poly2 >> ch2 >> poly3;
					int indx1 = poly1 - 1, indx2 = poly2 - 1, indx3 = poly3 - 1;
					vector<int>ids1, ids2, ids3;
					if (Is_Intersecting(shapes[indx1], shapes[indx2]))
					{
						ids1.push_back(indx1 + 1);		ids1.push_back(indx2 + 1);
						ids2.push_back(indx1 + 1);		ids2.push_back(indx2 + 1);
					}
					if (Is_Intersecting(shapes[indx2], shapes[indx3]))
					{
						ids2.push_back(indx2 + 1);		ids2.push_back(indx3 + 1);
						ids3.push_back(indx1 + 1);		ids3.push_back(indx3 + 1);
					}
					if (Is_Intersecting(shapes[indx1], shapes[indx3]))
					{
						ids1.push_back(indx1 + 1);		ids1.push_back(indx3 + 1);
						ids3.push_back(indx1 + 1);		ids3.push_back(indx3 + 1);
					}


					for (int i = 0; i < shapes.size(); i++)
					{
						if (i == indx1 || i == indx2||i==indx3)
							continue;
						if (Is_Intersecting(shapes[i], shapes[indx1]))
							ids1.push_back(i + 1);
						if (Is_Intersecting(shapes[i], shapes[indx2]))
							ids2.push_back(i + 1);
						if (Is_Intersecting(shapes[i], shapes[indx3]))
							ids3.push_back(i + 1);
					}
					int flag1 = 0,flag2=0;
					for (auto i : ids1)
					{
						for (auto j : ids2)
							if (i == j)
							{
								flag1 = 1;
								break;
							}
						for (auto k:ids3)
							if (i == k)
							{
								flag2 = 1;
								break;
							}
						
						if (flag1 == 1 && flag2 == 1)
							break;
					}
					if (ids1.empty() || ids2.empty() || ids3.empty())
						cout << "FALSE\n";
					else if (flag1 == 1 && flag2 == 1)
						cout << "TRUE\n";
					else
						cout << "FALSE\n";

				}

				if (Operation == "Maximum_Intersecting_Group")
				{
					int  max_num = 1;
					vector<int>ids;
					for (int i = 1; i < shapes.size(); i++)
					{
						if (Is_Intersecting(shapes[0], shapes[i]))
						{
							max_num++;
							//ids.push_back(1);
							ids.push_back(i + 1);
						}
					}
					int intersectes = 0;
					for (auto firstP : ids)
						for (auto secondP : ids)
							if (Is_Intersecting(shapes[firstP - 1], shapes[secondP - 1]))
								intersectes = 1;
							else
							{
								intersectes = 0;
								break;
							}
					if (intersectes != 1)
						while (!ids.empty())
							ids.pop_back();
					for (int i = 1; i < shapes.size(); i++)
					{
						int counter = 1;
						vector<int>temp;
						for (int j = 0; j < shapes.size(); j++)
							if (Is_Intersecting(shapes[i], shapes[j]))
							{
								counter++;
								temp.push_back(j + 1);
							}

						if (counter > max_num)
						{
							max_num = counter;
							while (!ids.empty())
								ids.pop_back();
							for (int k = 0; k < temp.size(); k++)
								ids.push_back(temp[k]);
						}
						//ids.push_back(i + 1);
						int intersected = 0;
						for (auto firstP : ids)
							for (auto secondP : ids)
								if (Is_Intersecting(shapes[firstP-1], shapes[secondP-1]))
									intersected = 1;
								else
								{
									intersected = 0;
									break;
								}
						if (intersected != 1)
							while (!ids.empty())
								ids.pop_back();

					}
					if (ids.empty())
						cout << "none" << endl;
					else
						for (int i = 0; i < ids.size(); i++)
						{
							cout << ids[i];
							if ((i != ids.size() - 1))
								cout << ",";
						}
					//cout << max_num;

				}

				if (Operation == "Maximum_Connected_Group")
				{
					int  max_num=1;
					vector<int>ids;
					for (int i = 1; i < shapes.size(); i++)
					{
						if (Is_Intersecting(shapes[0], shapes[i]))
						{
							max_num++;
							ids.push_back(1);
							ids.push_back(i + 1);
						}
					}
					for (int i = 1; i < shapes.size(); i++)
					{
						int counter = 1;
						vector<int>temp;
						for (int j = 0; j < shapes.size();j++)
							if (Is_Intersecting(shapes[i], shapes[j]))
							{
								counter++;
								temp.push_back(j + 1);
							}
								
						if (counter > max_num)
						{
							max_num = counter;
							while (!ids.empty())
								ids.pop_back();
							for (int k = 0; k < temp.size(); k++)
								ids.push_back(temp[k]);
							//ids.push_back(i + 1);

						}
					}
					if (ids.empty())
						cout << "none" << endl;
					else
						for (int i = 0; i < ids.size(); i++)
						{
							cout << ids[i];
							if ((i != ids.size() - 1))
								cout << ",";
						}
				//cout << max_num;

				}
	}

return 0;

}



/*
	int size = shapes.size();
	vfloat Float_x;
	for (int i = 0; i < size; i++)
	{
	Float_x = shapes[i].get_xCoords();
	for (int j = 0; j < Float_x.size(); j++)
	{
	cout << Float_x[j] << endl;
	}
	}

	int size=shapes[i].get_size();
						if (num_points > size)
							cout << i + 1;
						if (i != shapes.size() - 1)
							cout << ",";
*/
