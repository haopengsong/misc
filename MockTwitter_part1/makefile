BIN_DIR = exe
CXX = compile
CXXFLAG = -g -Wall

all: $(BIN_DIR)/twitter

$(BIN_DIR)/twitter: twitter.cpp $(BIN_DIR)/.dirstamp $(BIN_DIR)/datetime.o $(BIN_DIR)/tweet.o $(BIN_DIR)/user.o $(BIN_DIR)/twiteng.o
	$(CXX) $(CXXFLAG) -o $(BIN_DIR)/twitter $(BIN_DIR)/datetime.o $(BIN_DIR)/tweet.o $(BIN_DIR)/user.o $(BIN_DIR)/twiteng.o twitter.cpp

$(BIN_DIR)/datetime.o: datetime.cpp datetime.h
	$(CXX) $(CXXFLAG) -c datetime.cpp -o $(BIN_DIR)/datetime.o

$(BIN_DIR)/tweet.o: tweet.cpp tweet.h
	$(CXX) $(CXXFLAG) -c tweet.cpp -o $(BIN_DIR)/tweet.o

$(BIN_DIR)/user.o: user.cpp user.h
	$(CXX) $(CXXFLAG) -c user.cpp -o $(BIN_DIR)/user.o

$(BIN_DIR)/twiteng.o: twiteng.cpp twiteng.h
	$(CXX) $(CXXFLAG) -c twiteng.cpp -o $(BIN_DIR)/twiteng.o

$(BIN_DIR)/.dirstamp:
	mkdir -p  $(BIN_DIR)
	touch  $(BIN_DIR)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)