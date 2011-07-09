/**
 * Studying C++
 * Some bitwise operations
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>
#include <string>

#include "bitwise.h"

void dec_bin(int);
void printGroupPermissions();
void printUserPermissions(User*);

int main()
{
    // print out our permissions in binary format to better understanding
    printGroupPermissions();

    // create a new user, set the name and group
    User editor;
    editor.SetName("Fredi");
    editor.SetGroup(USER_EDITOR);

    // create a new user and set it as publisher
    User publisher;
    publisher.SetName("Mariana");
    publisher.SetGroup(USER_PUBLISHER);

    // print what Fredi can and cannot do
    printUserPermissions(&editor);

    printf("\n");

    // print what Mariana can and cannot do
    printUserPermissions(&publisher);

    return 0;
}

/**
 * convert decimal to binary and print the result
 * http://www.c.happycodings.com/Miscellaneous/code9.html
 */
void dec_bin(int number)
{
    int x, y;
    x = y = 0;

    for (y = 7; y >= 0; y--)
    {
        x = number / (1 << y);
        number = number - x * (1 << y);
        printf("%d", x);
    }

    printf("\n");
}

void printGroupPermissions()
{
    printf("READ:    ");
    dec_bin(PERM_READ);

    printf("EDIT:    ");
    dec_bin(PERM_EDIT);

    printf("PUBLISH: ");
    dec_bin(PERM_PUBLISH);

    printf("DELETE:  ");
    dec_bin(PERM_DELETE);

    printf("\n");

    printf("GUESTS CAN:     ");
    dec_bin(USER_GUEST);

    printf("EDITORS CAN:    ");
    dec_bin(USER_EDITOR);

    printf("MODERATORS CAN: ");
    dec_bin(USER_MODERATOR);

    printf("PUBLISHERS CAN: ");
    dec_bin(USER_PUBLISHER);

    printf("ADMINS CAN:     ");
    dec_bin(USER_ADMIN);

    printf("\n");
}

void printUserPermissions(User* user)
{
    std::string name = user->GetName();

    // check read
    if (user->Can(PERM_READ))
        printf("%s CAN read.\n", name.c_str());
    else
        printf("%s CANNOT read.\n", name.c_str());

    // check edit
    if (user->Can(PERM_EDIT))
        printf("%s CAN edit.\n", name.c_str());
    else
        printf("%s CANNOT edit.\n", name.c_str());

    // check publish
    if (user->Can(PERM_PUBLISH))
        printf("%s CAN publish.\n", name.c_str());
    else
        printf("%s CANNOT publish.\n", name.c_str());

    // check delete
    if (user->Can(PERM_DELETE))
        printf("%s CAN delete.\n", name.c_str());
    else
        printf("%s CANNOT delete.\n", name.c_str());
}
