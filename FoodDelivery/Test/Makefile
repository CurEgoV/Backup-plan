CC = g++
CFLAGS = -Wall -Wextra -std=c++14
INCLUDES = -I./Customer -I./Order -I./Delivery -I./Restaurant -I./IDGenerator -I./Restaurant_getter

SRCS = main.cpp \
       Customer/customer.cpp \
       Order/order.cpp \
       Delivery/delivery.cpp \
       Restaurant/restaurant.cpp \
       IDGenerator/IDGenerator.cpp \
       Restaurant_getter/restaurant_getter.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = my_program

$(TARGET):	$(OBJS)
	$(CC)	$(CFLAGS)	$(INCLUDES)	-o	$@	$(OBJS)

%.o:	%.cpp
	$(CC)	$(CFLAGS)	$(INCLUDES)	-c	$<	-o	$@

clean:
	$(RM)	$(OBJS)	$(TARGET)