#include "textview.h"

#include <iostream>
#include <string>

using std::cout;
using std::string;

void TextView::display(Board &b) const {
    cout << "                                   |" << b.get_criteria()[0]->get_display() << "|--" << b.get_goals()[0]->get_display() << "--|" << b.get_criteria()[1]->get_display() << "|\n";
    cout << "                                   /            \\\n";
    cout << "                                 " << b.get_goals()[1]->get_display() << "       0     " << b.get_goals()[2]->get_display() << "\n";
    cout << "                                 /     " << b.get_tiles()[0]->display_resource() << "   \\\n";
    cout << "                    |" << b.get_criteria()[2]->get_display() << "|--" << b.get_goals()[3]->get_display() << "--|" << b.get_criteria()[3]->get_display() << "|       " << b.get_tiles()[0]->display_roll_val() << "       |" << b.get_criteria()[4]->get_display() << "|--" << b.get_goals()[4]->get_display() << "--|" << b.get_criteria()[5]->get_display() << "|\n";
    cout << "                    /            \\     " << b.get_tiles()[0]->display_goose() << "      /            \\\n";
    cout << "                  " << b.get_goals()[5]->get_display() << "       1     " << b.get_goals()[6]->get_display() << "             " << b.get_goals()[7]->get_display() << "       2     " << b.get_goals()[8]->get_display() << "\n";
    cout << "                  /     " << b.get_tiles()[1]->display_resource() << "   \\            /     " << b.get_tiles()[2]->display_resource() << "   \\\n";
    cout << "     |" << b.get_criteria()[6]->get_display() << "|--" << b.get_goals()[9]->get_display() << "--|" << b.get_criteria()[7]->get_display() << "|       " << b.get_tiles()[1]->display_roll_val() << "       |" << b.get_criteria()[8]->get_display() << "|--" << b.get_goals()[10]->get_display() << "--|" << b.get_criteria()[9]->get_display() << "|       " << b.get_tiles()[2]->display_roll_val() << "       |" << b.get_criteria()[10]->get_display() << "|--" << b.get_goals()[11]->get_display() << "--|" << b.get_criteria()[11]->get_display() << "|\n";
    cout << "     /            \\     " << b.get_tiles()[1]->display_goose() << "      /            \\     " << b.get_tiles()[2]->display_goose() << "      /            \\\n";
    cout << "   " << b.get_goals()[12]->get_display() << "       3     " << b.get_goals()[13]->get_display() << "             " << b.get_goals()[14]->get_display() << "       4     " << b.get_goals()[15]->get_display() << "             " << b.get_goals()[16]->get_display() << "       5     " << b.get_goals()[17]->get_display() << "\n";
    cout << "   /     " << b.get_tiles()[3]->display_resource() << "   \\            /     " << b.get_tiles()[4]->display_resource() << "   \\            /     " << b.get_tiles()[5]->display_resource() << "   \\\n";
    cout << "|" << b.get_criteria()[12]->get_display() << "|       " << b.get_tiles()[3]->display_roll_val() << "       |" << b.get_criteria()[13]->get_display() << "|--" << b.get_goals()[18]->get_display() << "--|" << b.get_criteria()[14]->get_display() << "|       " << b.get_tiles()[4]->display_roll_val() << "       |" << b.get_criteria()[15]->get_display() << "|--" << b.get_goals()[19]->get_display() << "--|" << b.get_criteria()[16]->get_display() << "|       " << b.get_tiles()[5]->display_roll_val() << "       |" << b.get_criteria()[17]->get_display() << "|\n";
    cout << "   \\     " << b.get_tiles()[3]->display_goose() << "      /            \\     " << b.get_tiles()[4]->display_goose() << "      /            \\     " << b.get_tiles()[5]->display_goose() << "      /\n";
    cout << "   " << b.get_goals()[20]->get_display() << "             " << b.get_goals()[21]->get_display() << "       6     " << b.get_goals()[22]->get_display() << "             " << b.get_goals()[23]->get_display() << "       7     " << b.get_goals()[24]->get_display() << "             " << b.get_goals()[25]->get_display() << "\n";
    cout << "     \\            /     " << b.get_tiles()[6]->display_resource() << "   \\            /     " << b.get_tiles()[7]->display_resource() << "   \\            /\n";
    cout << "     |" << b.get_criteria()[18]->get_display() << "|--" << b.get_goals()[26]->get_display() << "--|" << b.get_criteria()[19]->get_display() << "|       " << b.get_tiles()[6]->display_roll_val() << "       |" << b.get_criteria()[20]->get_display() << "|--" << b.get_goals()[27]->get_display() << "--|" << b.get_criteria()[21]->get_display() << "|       " << b.get_tiles()[7]->display_roll_val() << "       |" << b.get_criteria()[22]->get_display() << "|--" << b.get_goals()[28]->get_display() << "--|" << b.get_criteria()[23]->get_display() << "|\n";
    cout << "     /            \\     " << b.get_tiles()[6]->display_goose() << "      /            \\     " << b.get_tiles()[7]->display_goose() << "      /            \\\n";
    cout << "   " << b.get_goals()[29]->get_display() << "       8     " << b.get_goals()[30]->get_display() << "             " << b.get_goals()[31]->get_display() << "       9     " << b.get_goals()[32]->get_display() << "             " << b.get_goals()[33]->get_display() << "      10     " << b.get_goals()[34]->get_display() << "\n";
    cout << "   /     " << b.get_tiles()[8]->display_resource() << "   \\            /     " << b.get_tiles()[9]->display_resource() << "   \\            /     " << b.get_tiles()[10]->display_resource() << "   \\\n";
    cout << "|" << b.get_criteria()[24]->get_display() << "|       " << b.get_tiles()[8]->display_roll_val() << "       |" << b.get_criteria()[25]->get_display() << "|--" << b.get_goals()[35]->get_display() << "--|" << b.get_criteria()[26]->get_display() << "|       " << b.get_tiles()[9]->display_roll_val() << "       |" << b.get_criteria()[27]->get_display() << "|--" << b.get_goals()[36]->get_display() << "--|" << b.get_criteria()[28]->get_display() << "|       " << b.get_tiles()[10]->display_roll_val() << "       |" << b.get_criteria()[29]->get_display() << "|\n";
    cout << "   \\     " << b.get_tiles()[8]->display_goose() << "      /            \\     " << b.get_tiles()[9]->display_goose() << "      /            \\     " << b.get_tiles()[10]->display_goose() << "      /\n";
    cout << "   " << b.get_goals()[37]->get_display() << "             " << b.get_goals()[38]->get_display() << "      11     " << b.get_goals()[39]->get_display() << "             " << b.get_goals()[40]->get_display() << "      12     " << b.get_goals()[41]->get_display() << "             " << b.get_goals()[42]->get_display() << "\n";
    cout << "     \\            /     " << b.get_tiles()[11]->display_resource() << "   \\            /     " << b.get_tiles()[12]->display_resource() << "   \\            /\n";
    cout << "     |" << b.get_criteria()[30]->get_display() << "|--" << b.get_goals()[43]->get_display() << "--|" << b.get_criteria()[31]->get_display() << "|       " << b.get_tiles()[11]->display_roll_val() << "       |" << b.get_criteria()[32]->get_display() << "|--" << b.get_goals()[44]->get_display() << "--|" << b.get_criteria()[33]->get_display() << "|       " << b.get_tiles()[12]->display_roll_val() << "       |" << b.get_criteria()[34]->get_display() << "|--" << b.get_goals()[45]->get_display() << "--|" << b.get_criteria()[35]->get_display() << "|\n";
    cout << "     /            \\     " << b.get_tiles()[11]->display_goose() << "      /            \\     " << b.get_tiles()[12]->display_goose() << "      /            \\\n";
    cout << "   " << b.get_goals()[46]->get_display() << "      13     " << b.get_goals()[47]->get_display() << "             " << b.get_goals()[48]->get_display() << "      14     " << b.get_goals()[49]->get_display() << "             " << b.get_goals()[50]->get_display() << "      15     " << b.get_goals()[51]->get_display() << "\n";
    cout << "   /     " << b.get_tiles()[13]->display_resource() << "   \\            /     " << b.get_tiles()[14]->display_resource() << "   \\            /     " << b.get_tiles()[15]->display_resource() << "   \\\n";
    cout << "|" << b.get_criteria()[36]->get_display() << "|       " << b.get_tiles()[13]->display_roll_val() << "       |" << b.get_criteria()[37]->get_display() << "|--" << b.get_goals()[52]->get_display() << "--|" << b.get_criteria()[38]->get_display() << "|       " << b.get_tiles()[14]->display_roll_val() << "       |" << b.get_criteria()[39]->get_display() << "|--" << b.get_goals()[53]->get_display() << "--|" << b.get_criteria()[40]->get_display() << "|       " << b.get_tiles()[15]->display_roll_val() << "       |" << b.get_criteria()[41]->get_display() << "|\n";
    cout << "   \\     " << b.get_tiles()[13]->display_goose() << "      /            \\     " << b.get_tiles()[14]->display_goose() << "      /            \\     " << b.get_tiles()[15]->display_goose() << "      /\n";
    cout << "   " << b.get_goals()[54]->get_display() << "             " << b.get_goals()[55]->get_display() << "      16     " << b.get_goals()[56]->get_display() << "             " << b.get_goals()[57]->get_display() << "      17     " << b.get_goals()[58]->get_display() << "             " << b.get_goals()[59]->get_display() << "\n";
    cout << "     \\            /     " << b.get_tiles()[16]->display_resource() << "   \\            /     " << b.get_tiles()[17]->display_resource() << "   \\            /\n";
    cout << "     |" << b.get_criteria()[42]->get_display() << "|--" << b.get_goals()[60]->get_display() << "--|" << b.get_criteria()[43]->get_display() << "|       " << b.get_tiles()[16]->display_roll_val() << "       |" << b.get_criteria()[44]->get_display() << "|--" << b.get_goals()[61]->get_display() << "--|" << b.get_criteria()[45]->get_display() << "|       " << b.get_tiles()[17]->display_roll_val() << "       |" << b.get_criteria()[46]->get_display() << "|--" << b.get_goals()[62]->get_display() << "--|" << b.get_criteria()[47]->get_display() << "|\n";
    cout << "                  \\     " << b.get_tiles()[16]->display_goose() << "      /            \\     " << b.get_tiles()[17]->display_goose() << "      /\n";
    cout << "                  " << b.get_goals()[63]->get_display() << "             " << b.get_goals()[64]->get_display() << "      18     " << b.get_goals()[65]->get_display() << "             " << b.get_goals()[66]->get_display() << "\n";
    cout << "                    \\            /     " << b.get_tiles()[18]->display_resource() << "   \\            /\n";
    cout << "                    |" << b.get_criteria()[48]->get_display() << "|--" << b.get_goals()[67]->get_display() << "--|" << b.get_criteria()[49]->get_display() << "|       " << b.get_tiles()[18]->display_roll_val() << "       |" << b.get_criteria()[50]->get_display() << "|--" << b.get_goals()[68]->get_display() << "--|" << b.get_criteria()[51]->get_display() << "|\n";
    cout << "                                 \\     " << b.get_tiles()[18]->display_goose() << "      /\n";
    cout << "                                 " << b.get_goals()[69]->get_display() << "             " << b.get_goals()[70]->get_display() << "\n";
    cout << "                                   \\            /\n";
    cout << "                                   |" << b.get_criteria()[52]->get_display() << "|--" << b.get_goals()[71]->get_display() << "--|" << b.get_criteria()[53]->get_display() << "|" << std::endl;


    // cout << "                                   |32|--44--|33|\n";
    // cout << "                                   /            \\\n";
    // cout << "                                 31       9     32\n";
    // cout << "                                 /     CAFFEINE   \\\n";
    // cout << "                    |25|--35--|26|        2       |27|--36--|28|\n";
    // cout << "                    /            \\                /            \\\n";
    // cout << "                  38             39             40             41\n";
    // cout << "                  /                \\            /                \\\n";
    // cout << "     |18|--26--|19|       11       |20|--27--|21|        3       |22|--28--|23|\n";
    // cout << "     /            \\                /            \\                /            \\\n";
    // cout << "   29       8     30             31       9     32             33             34\n";
    // cout << "   /     STUDY      \\            /     CAFFEINE   \\            /     CAFFEINE   \\\n";
    // cout << "|24|        8       |25|--35--|26|        2       |27|--36--|28|        6       |29|\n";
    // cout << "   \\                /            \\                /            \\                /\n";
    // cout << "   37             38             39             40             41             42\n";
    // cout << "     \\            /                \\            /                \\            /\n";
    // cout << "     |30|--43--|31|       11       |32|--44--|33|        3       |34|--45--|35|\n";
    // cout << "     /            \\                /            \\                /            \\\n";
    // cout << "   29       8     30             31       9     32             33             34\n";
    // cout << "   /     STUDY      \\            /     CAFFEINE   \\            /     CAFFEINE   \\\n";
    // cout << "|24|        8       |25|--35--|26|        2       |27|--36--|28|        6       |29|\n";
    // cout << "   \\                /            \\     GEESE      /            \\                /\n";
    // cout << "   37             38             39             40             41             42\n";
    // cout << "     \\            /                \\            /                \\            /\n";
    // cout << "     |30|--43--|31|       11       |32|--44--|33|        3       |34|--45--|35|\n";
    // cout << "     /            \\                /            \\                /            \\\n";
    // cout << "   29       8     30             31       9     32             33             34\n";
    // cout << "   /     STUDY      \\            /     CAFFEINE   \\            /     CAFFEINE   \\\n";
    // cout << "|24|        8       |25|--35--|26|        2       |27|--36--|28|        6       |29|\n";
    // cout << "   \\                /            \\                /            \\                /\n";
    // cout << "   37             38             39             40             41             42\n";
    // cout << "     \\            /                \\            /                \\            /\n";
    // cout << "     |30|--43--|31|       11       |32|--44--|33|        3       |34|--45--|35|\n";
    // cout << "                  \\                /            \\                /\n";
    // cout << "                  30             31             32             33\n";
    // cout << "                    \\            /                \\            /\n";
    // cout << "                    |10|--10--|10|                |10|--10--|10|\n";
    // cout << "                                 \\                /\n";
    // cout << "                                 39             40\n";
    // cout << "                                   \\            /\n";
    // cout << "                                   |32|--44--|33|" << std::endl;
