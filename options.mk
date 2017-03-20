
# Set what option should compile into the OKPrompt

# Maximal memory available for persistent variables
OBP_Variables_MAX_SIZE = $(EE_MAX_SIZE)

# set builddate
BUILD_DATE = $(shell date)

DASH_VARS = \
	-DOBP_Variables_MAX_SIZE=$(OBP_Variables_MAX_SIZE) \
	-DBUILD_DATE="\"$(BUILD_DATE)\""
	