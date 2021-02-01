if [ ! -d "build" ]; then
mkdir build
fi

cd build

cmake ../

echo "********************"
make
echo "********************"

./quantity-test
