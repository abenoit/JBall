CXX=g++
CXXFLAGS= -g -Wall -pedantic
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
EXEC = JBall
DIRCFG = config
DIRDATA = data
EXECFG = doxy.cfg
EXECPATH = .
OBJ  = main.o OptionsController.o IntroView.o Bouton.o Slider.o util.o GameModel.o Ball.o Wall.o GameView.o GameController.o vieMoins.o gameOver.o niveauSuivant.o SegaView.o OptionsView.o HighScoreModel.o HighScoreView.o HighScoreController.o Controller.o Vue.o Model.o IntroController.o newScore.o menuChoix.o

all: $(EXEC)

JBall: $(OBJ)
	$(CXX) -o $(EXECPATH)/$@ $(OBJ) $(LDFLAGS)

%: %.o
	$(CXX) -o $@ -c $< $(CXXFLAGS)

doc:
	@doxygen $(EXECPATH)/$(DIRCFG)/$(EXECFG)

clean:
	@rm -r *~ *.o $(EXECPATH)/$(DIRDATA)/*~

mrproper:
	@rm -rf *~ *.o html $(EXECPATH)/$(EXEC) $(EXECPATH)/$(DIRDATA)/*~
