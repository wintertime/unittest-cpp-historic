CC = g++
CCFLAGS = -g -ansi -Wall -DLINUX
SED = sed
MV = mv
RM = rm

.SUFFIXES: .o .cpp

lib = TestUnit++.a
test = TestTestUnit++

src = src/AssertException.cpp \
	src/HTMLTestReporter.cpp \
	src/PrintfTestReporter.cpp \
	src/ReportAssert.cpp \
	src/Test.cpp \
	src/TestReporter.cpp \
	src/TestResults.cpp \
	src/TestRunner.cpp \
	src/Linux/SignalTranslator.cpp \
	src/Linux/TimeHelpers.cpp

test_src = src/tests/Main.cpp \
	src/tests/TestAssertHandler.cpp \
	src/tests/TestChecks.cpp \
	src/tests/TestUnitTestCpp.cpp \
	src/tests/TestTest.cpp \
	src/tests/TestTestResults.cpp \
	src/tests/TestTestRunner.cpp \
	src/tests/TestCheckMacros.cpp \
	src/tests/TestTestRegistrar.cpp


objects = $(patsubst %.cpp, %.o, $(src))
test_objects = $(patsubst %.cpp, %.o, $(test_src))
dependencies = $(subst .o,.d,$(objects))
test_dependencies = $(subst .o,.d,$(test_objects))

define make-depend
  $(CC) $(CCFLAGS) -M $1 | \
  $(SED) -e 's,\($(notdir $2)\) *:,$(dir $2)\1: ,' > $3.tmp
  $(SED) -e 's/#.*//' \
      -e 's/^[^:]*: *//' \
      -e 's/ *\\$$//' \
      -e '/^$$/ d' \
      -e 's/$$/ :/' $3.tmp >> $3.tmp
  $(MV) $3.tmp $3
endef


all: $(test)


$(lib): $(objects) 
	@echo Creating $(lib) library...
	@ar cr $(lib) $(objects)
    
$(test): $(lib) $(test_objects)
	@echo Linking $(test)...
	@$(CC) -o $(test) $(test_objects) $(lib)
	@echo Running unit tests...
	@./$(test)

clean:
	-@$(RM) $(objects) $(test_objects) $(dependencies) $(test_dependencies) $(test) $(lib) 2> /dev/null

%.o : %.cpp
	@echo $<
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@$(CC) $(CCFLAGS) -c $< -o $(patsubst %.cpp, %.o, $<)


ifneq "$(MAKECMDGOALS)" "clean"
-include $(dependencies)
-include $(test_dependencies)
endif
