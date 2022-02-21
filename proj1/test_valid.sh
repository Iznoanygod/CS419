echo "------- auth project test -------"
echo "-------    Andrew Park    -------"
echo ""
echo "Testing user creation and authentication"
echo "Creating user user1 with no password"
./auth AddUser user1
echo "Creating user user2 with password"
./auth AddUser user2 password1
echo "Creating user user1"
./auth AddUser user1
echo "Creating 3 more users"
./auth AddUser user3
./auth AddUser user4
./auth AddUser user5
echo "Authenticate user1 with wrong password"
./auth Authenticate user1 wrongpassword
echo "Authenticate user1 with no password"
./auth Authenticate user1
echo "Authenticate user2 with wrong password"
./auth Authenticate user2 wrongpassword
echo "Authenticate user2 with password"
./auth Authenticate user2 password1

echo ""
echo "Testing domain creation"
echo "Adding user1 to domain1"
./auth SetDomain user1 domain1
echo "Adding user2 to domain1"
./auth SetDomain user2 domain1
echo "Adding user3 to domain2"
./auth SetDomain user3 domain2
echo "Adding user4 to domain2"
./auth SetDomain user4 domain2
echo "Adding user5 to all domains"
./auth SetDomain user5 domain1
./auth SetDomain user5 domain2
echo "Show domain1"
./auth DomainInfo domain1
echo "Show domain2"
./auth DomainInfo domain2
echo "Show domain3"
./auth DomainInfo domain3
echo "Adding user5 to domain3"
./auth SetDomain user5 domain3

echo ""
echo "Testing type creation"
echo "Adding object1 to type1"
./auth SetType object1 type1
echo "Adding object2 to type1"
./auth SetType object2 type1
echo "Adding object3 to type2"
./auth SetType object3 type2
echo "Adding object4 to type2"
./auth SetType object4 type2
echo "Adding object5 to type3"
./auth SetType object5 type3
echo "Showing type1"
./auth TypeInfo type1
echo "Showing type2"
./auth TypeInfo type2
echo "Showing type3"
./auth TypeInfo type3
echo "Showing type4"
./auth TypeInfo type4

echo ""
echo "Testing access"
echo "Adding read access to domain1 for type1"
./auth AddAccess read domain1 type1
echo "Adding write access to domain2 for type2"
./auth AddAccess write domain2 type2
echo "Adding exec access to domain3 for type3"
./auth AddAccess exec domain3 type3
echo "Testing if user1 can read object1"
./auth CanAccess read user1 object1
echo "Testing if user1 can read object2"
./auth CanAccess read user1 object2
echo "Testing if user1 can read object3"
./auth CanAccess read user1 object3
echo "Testing if user2 can read object1"
./auth CanAccess read user2 object1
echo "Testing if user2 can write object3"
./auth CanAccess write user2 object3
echo "Testing if user3 can write object3"
./auth CanAccess write user3 object3
echo "Testing if user3 can write object4"
./auth CanAccess write user3 object4
echo "Testing if user3 can write object1"
./auth CanAccess write user3 object1
echo "Testing if user5 can read object1"
./auth CanAccess read user5 object1
echo "Testing if user5 can write object3"
./auth CanAccess write user5 object3
echo "Testing if user5 can exec object5"
./auth CanAccess exec user5 object5
