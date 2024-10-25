#include "TestGLogApplication.h"


#include <utilities/GFileIOHandler.h>
#include <utilities/GException.h>
#include <cmdline/GCommandLineArgument.h>


TestGLogApplication::TestGLogApplication()
{
}


TestGLogApplication::~TestGLogApplication()
{
}


void 
TestGLogApplication::SetUp()
{
      l->SetLogTarget("--target-file");    
}


void 
TestGLogApplication::TearDown()
{
    g_file()->Delete(fValidCommands);
    g_file()->Delete(fNotValidCommands);
}

TEST_F(TestGLogApplication, get_argument )
{
	GLogApplication *g = new GLogApplication();
  g->InitLogArgs();
	EXPECT_NE(nullptr, g->GetArgument("-loglevel")  );
  delete g;
}


TEST_F(TestGLogApplication,   remove_argument )
{
	GLogApplication *g = new GLogApplication();
	g->InitLogArgs();
  EXPECT_NE(nullptr, g->GetArgument("-loglevel")  );
	size_t size_before = g->GetArguments()->size();
	g->RemoveArgument("-loglevel");
	EXPECT_EQ(nullptr, g->GetArgument("-loglevel")  );
	size_t size_after = g->GetArguments()->size();
	EXPECT_EQ(size_after, size_before -1 );

}


TEST_F(TestGLogApplication, cmdline_from_file)
{
        SET_LOGTARGET("1111");  
        g_file()->GFileIOHandler::Append(fValidCommands, "%s", "-loglevel --all -logtarget 0000 --target-file");
        EXPECT_EQ("-loglevel --all -logtarget 0000 --target-file", g_file()->ReadLastLine(fValidCommands));
        g_file()->Append(fNotValidCommands, "%s", "gibberish");
        EXPECT_EQ("gibberish", g_file()->ReadLastLine(fNotValidCommands));
        EXPECT_NO_THROW(GLogApplication( GFileName_t(fValidCommands) )  );
        EXPECT_ANY_THROW(GLogApplication(GFileName_t(fNotValidCommands) ));

        try
        {
        GLogApplication( GFileName_t(fValidCommands) ); 
        }
        catch( GException &e )
        {
          cerr  << e.what() << endl;
        }

}



TEST_F(TestGLogApplication, extra_arguments)
{
    double f1, f2, f3 = 0;
    GArgument *arg1, *arg2, *arg3;

    arg1 = new  GCommandLineArgument<double>("-fval1", &f1);
    arg2 = new  GCommandLineArgument<double>("-fval2", &f2);
    arg3 = new  GCommandLineArgument<double>("-fval3", &f3);

    vector<GArgument *> all_args = { arg1, arg2, arg3 };

    // We expect an execption for both filenames because the files are emty (they are delet in th teardown function)
    
    vector<GArgument *>  arg1_v = {arg1};

    
    EXPECT_ANY_THROW(GLogApplication(GFileName_t(fValidCommands), &arg1_v));
    EXPECT_ANY_THROW(GLogApplication(GFileName_t(fNotValidCommands), &arg1_v ) );

    g_file()->Append(fValidCommands, "%s", "-fval1 3.1415901");
    g_file()->Append(fNotValidCommands, "%s", "-nonexisting 3.14");

    EXPECT_NO_THROW(GLogApplication(GFileName_t(fValidCommands),  &arg1_v ));
    EXPECT_NEAR(f1, 3.1415901, 0.001);
    g_file()->Delete(fValidCommands);
    g_file()->Append(fValidCommands, "%s", "-fval1 3.1415901  -fval2  1.61803  -fval3  0.76422");
    EXPECT_NO_THROW(  GLogApplication(GFileName_t(fValidCommands),  &all_args  ));
    EXPECT_NEAR(f1, 3.1415901, 0.0001);
    EXPECT_NEAR(f2, 1.61803, 0.0001);
    EXPECT_NEAR(f3, 0.76422, 0.0001);
    
    delete arg1;
    delete arg2;
    delete arg3;
    
}
 




