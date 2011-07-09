/**
 * Fredi Machado
 * http://github.com/fredi
 */

// declare our permissions, values must be in power of two.
enum Permissions
{
    PERM_READ       = 1, // binary: 0001
    PERM_EDIT       = 2, // binary: 0010
    PERM_PUBLISH    = 4, // binary: 0100
    PERM_DELETE     = 8  // binary: 1000
};

// declare our groups setting what each group can do
enum UserGroups
{
    USER_GUEST      = PERM_READ, // guest can read
    USER_EDITOR     = USER_GUEST | PERM_EDIT, // editor can do what guests can plus edit
    USER_MODERATOR  = USER_EDITOR | PERM_PUBLISH, // moderator can read, edit and publish
    USER_PUBLISHER  = USER_MODERATOR & ~PERM_EDIT, // publishers can do what moderators can but not edit
    USER_ADMIN      = USER_MODERATOR | PERM_DELETE // admin can do what moderators can plus delete
};

/**
 * Simple user class
 * most functions here are self-explanatory
 */
class User
{
    public:
        void SetName(const std::string& name) { _name = name; }

        const char* GetName() const { return _name.c_str(); }

        void SetGroup(int group) { _group = group; }

        // check if the user can do based on his group (using bitwise &)
        bool Can(int action) { return _group & action; }

    private:
        int _group;
        std::string _name;
};