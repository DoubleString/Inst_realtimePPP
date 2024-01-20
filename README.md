#BUILD
make build
cmake ../
make 

#SET LINK LIBRARY
export LD_LIBRARY_PATH=$(pwd)/libs

#RUN
cp build/ppp configures
./ppp

##
FOR MORE INFORMATION,PLEASE CONTACT jtaowhu@whu.edu.cn
