echo "------- auth project test -------"
echo "-------    Andrew Park    -------"
echo ""
echo "Testing user creation"
echo "Creating user with no username"
./auth AddUser ""
echo "AddUser with no arguments"
./auth AddUser
echo "AddUser with too many arguments"
./auth AddUser arg1 arg2 arg3 arg4
echo "Authenticate with no username"
./auth Authenticate
echo "Authenticate with too many arguments"
./auth Authenticate arg1 arg2 arg3

echo ""
echo "Testing domains"
echo "Testing SetDomain with no arguments"
./auth SetDomain
echo "Testing SetDomain with empty arguments"
./auth SetDomain "" ""
echo "Testing SetDomain with too many arguments"
./auth SetDomain arg1 arg2 arg3 arg4
echo "Testing DomainInfo with no arguments"
./auth DomainInfo
echo "Testing DomainInfo with empty arguments"
./auth DomainInfo ""
echo "Testing DomainInfo with too many arguments"
./auth DomainInfo arg1 arg2 arg3

echo ""
echo "Testing types"
echo "Testing SetType with no arguments"
./auth SetType
echo "Testing SetType with empty arguments"
./auth SetType "" ""
echo "Testing SetType with too many arguments"
./auth SetType arg1 arg2 arg3
echo "Testing TypeInfo with no arguments"
./auth TypeInfo
echo "Testing TypeInfo with empty arguments"
./auth TypeInfo ""
echo "Testing TypeInfo with too many arguments"
./auth TypeInfo arg1 arg2 arg3

echo ""
echo "Testing access "
echo "Testing AddAccess with no arguments"
./auth AddAccess
echo "Testing AddAccess with empty arguments"
./auth AddAccess "" "" ""
echo "Testing AddAccess with too many arguments"
./auth SetType arg1 arg2 arg3 arg4 arg5
echo "Testing CanAccess with no arguments"
./auth CanAccess
echo "Testing CanAccess with empty arguments"
./auth CanAccess "" "" ""
echo "Testing CanAccess with too many arguments"
./auth CanAccess arg1 arg2 arg3 arg4 arg5

echo ""
echo "Testing syntax error"
./auth random
./auth

