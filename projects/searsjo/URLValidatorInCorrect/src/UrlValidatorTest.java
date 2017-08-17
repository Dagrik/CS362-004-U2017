/* Jason Fisher, Josh Sears, David Yates
 * CS362-400, Su17
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("'http://www.amazon.com' : Expect true : Result " + urlVal.isValid("http://www.amazon.com"));
	   System.out.println();
	   
	   //Test adding one URL element at a time until max elements reached
	   System.out.println("Testing adding one URL element at a time until full");
	   //blank space should return false
	   System.out.println("Blank space ' ' : Expect false : Result " + urlVal.isValid(""));
	   //scheme only - Should return false
	   System.out.println("'http://' : Expect false : Result " + urlVal.isValid("http://"));
	   //correct scheme and authority - true
	   System.out.println("'https://oregonstate.edu' : Expect true : Result " + urlVal.isValid("https://oregonstate.edu"));
	   //correct scheme, authority, and port - true
	   System.out.println("'http://www.netflix.com:80' : Expect true : Result " + urlVal.isValid("http://www.netflix.com:80"));
	   //correct scheme, authority, port, and path - true
	   System.out.println("'http://www.netflix.com:80/help' : Expect true : Result " + urlVal.isValid("http://www.netflix.com:80/help"));
	   //correct scheme, authority, port, path, and query - true
	   System.out.print("'http://www.netflix.com:80/help?action=edit' : Expect true : Result ");
	   System.out.println(urlVal.isValid("http://www.netflix.com:80/help?action=edit"));
	   System.out.println();

	   //Test URLs with one missing component
	   System.out.println("Testing URLs with one missing element");
	   //correct scheme, port, path, and query but missing authority - false
	   System.out.print("'http://:80/help?action=edit' : Expect false : Result ");
	   System.out.println(urlVal.isValid("http://:80/help?action=edit"));
	   //correct scheme, authority, path, and query - missing port - true
	   System.out.print("'http://www.netflix.com/help?action=edit' : Expect true : Result ");
	   System.out.println(urlVal.isValid("http://www.netflix.com/help?action=edit"));
	   //correct scheme, authority, and path - missing port - true
	   //query removed due to observed bug when query added
	   System.out.print("'http://www.netflix.com/help' : Expect true : Result ");
	   System.out.println(urlVal.isValid("http://www.netflix.com/help"));	   
	   //correct scheme, authority, port but missing path - false
	   System.out.print("'http://www.netflix.com:80' : Expect true : Result ");
	   System.out.println(urlVal.isValid("http://www.netflix.com:80"));
	   //correct authority, port, path but missing scheme - true
	   System.out.print("'www.netflix.com:80/help' : Expect false : Result ");
	   System.out.println(urlVal.isValid("www.netflix.com:80/help"));
	   System.out.println();

	   //Test URLs with one incorrect component
	   System.out.println("Testing URLs with one incorrect element");
	   //incorrect scheme, correct authority, port, and path, no query - false
	   System.out.print("'http//www.netflix.com:80/help' : Expect false : Result ");
	   System.out.println(urlVal.isValid("http//www.netflix.com:80/help"));	 
	   //incorrect scheme, correct authority, port, and path, no query - false
	   System.out.print("'ftp:////www.netflix.com:80/help' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp:////www.netflix.com:80/help"));	 
	   //incorrect authority, correct scheme, port, and path, no query - false
	   System.out.print("'ftp://*1.netflix.com:80/help' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp://*1.netflix.com:80/help"));
	   //incorrect port, correct authority, scheme, and path, no query - false
	   System.out.print("'ftp://www.netflix.com:-5/help' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:-5/help"));	   
	   //incorrect path, correct authority, scheme, and port, no query - false
	   System.out.print("'ftp://www.netflix.com:5/..help/.' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:5/..help/"));
	   System.out.println();

	   //Check authority as IP address boundary cases
	   System.out.println("Testing authority IP address boundaries");
	   //correct scheme and authority with authority as min IP address - true
	   System.out.print("'https://0.0.0.0' : Expect true : Result ");
	   System.out.println(urlVal.isValid("https://0.0.0.0"));
	   //correct scheme and authority with authority as max IP address - true
	   System.out.print("'https://255.255.255.255' : Expect true : Result ");
	   System.out.println(urlVal.isValid("https://255.255.255.255"));
	   //correct scheme and authority with authority as max+1 IP address - false
	   System.out.print("'https://256.256.256.256' : Expect false : Result ");
	   System.out.println(urlVal.isValid("https://256.256.256.256"));
	   //correct scheme and authority with authority as min-1 IP address - false
	   System.out.print("'https://-1.-1.-1.-1' : Expect false : Result ");
	   System.out.println(urlVal.isValid("https://-1.-1.-1.-1"));
	   System.out.println();
	   
	   //Check port number boundary cases
	   System.out.println("Testing port boundaries");
	   //correct scheme and authority with min port - true
	   System.out.print("'ftp://www.netflix.com:0' : Expect true : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:0"));
	   //correct scheme and authority with max port - true
	   System.out.print("'ftp://www.netflix.com:65535' : Expect true : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:65535"));	
	   //correct scheme and authority with min-1 port - false
	   System.out.print("'ftp://www.netflix.com:-1' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:-1"));
	   //correct scheme and authority with max+1 port - true
	   System.out.print("'ftp://www.netflix.com:65536' : Expect false : Result ");
	   System.out.println(urlVal.isValid("ftp://www.netflix.com:65536"));	   
   }
   
   
   public void testYourFirstPartition(){

	System.out.println("First Partition Test:  Scheme");

	UrlValidator current = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	//4 valid schemes - should pass
	if(	!current.isValid("http://www.amazon.com") ||
		!current.isValid("ftp://www.amazon.com") ||
		!current.isValid("h3t://www.amazon.com") ||
		!current.isValid("https://www.amazon.com")){


		System.out.println("Scheme Partition Test Failed! Valid schemes identified as invalid");

	}
	else{

		System.out.println("Scheme Partition Test Passed! Valid schemes correctly identified as valid");

	}

	//4 invaid schemes - should fail
	if(	current.isValid("htttp://www.amazon.com") ||
		current.isValid("h33t://www.amazon.com") ||
		current.isValid("fftp://www.amazon.com") ||
		current.isValid("httpss://www.amazon.com")){


		System.out.println("Scheme Partition Test Failed! Invalid schemes identified as valid");

	}


	else{

		System.out.println("Scheme Partition Test Passed! Invalid schemes correctly identified as invalid");

	}
   
   }
   
   public void testYourSecondPartition(){

       System.out.println("Second Partition Test:  Authority");

       UrlValidator current = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       // 5 valid authorities - should pass
       if(     !current.isValid("http://www.amazon.com") ||
               !current.isValid("http://www.amazon.gov") ||
               !current.isValid("http://www.amazon.edu") ||
               !current.isValid("http://www.amazon.me") ||
               !current.isValid("http://255.255.255.255")){


               System.out.println("Authority Partition Test Failed! Valid authorities identified as invalid");

       }
       else{

               System.out.println("Authority Partition Test Passed! Valid authorities correctly identified as valid");

       }

       //5 invaid authorities - should fail
       if(     current.isValid("http://www.amazon.om") ||
               current.isValid("http://www.amazon.gv") ||
               current.isValid("http://www.amazon.ed") ||
               current.isValid("http://www.amazon.you") ||
              	current.isValid("http://256.256.256.256")){


               System.out.println("Authority Partition Test Failed! Invalid authorities identified as valid");

      	}


       else{

               System.out.println("Authority Partition Test Passed! Invalid authorities correctly identified as invalid");

       }

  }   


  public void testYourThirdPartition(){

       System.out.println("Third Partition Test: Port");

       UrlValidator current = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       // 5 valid portss - should pass
       if(     !current.isValid("http://www.amazon.com:0") ||
               !current.isValid("http://www.amazon.com:80") ||
               !current.isValid("http://www.amazon.com:1111") ||
               !current.isValid("http://www.amazon.com:22222") ||
               !current.isValid("http://www.amazon.com:65535")){


               System.out.println("Port Partition Test Failed! Valid ports identified as invalid");

       }
	else{

            	System.out.println("Port Partition Test Passed! Valid ports correctly identified as valid");

       }

	//3 invalid ports - should fail
       if(     current.isValid("http://www.amazon.com:-1") ||
               current.isValid("http://www.amazon.com:abcd") ||
               current.isValid("http://www.amazon.com:65536")){


               System.out.println("Port Partition Test Failed! Invalid ports identified as valid");

       }


	else{

            	System.out.println("Port Partition Test Passed! Invalid ports correctly identified as invalid");

      	}

  }   


  public void testYourFourthPartition(){

       System.out.println("Fourth Partition Test: Path");

       UrlValidator current = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       // 3 valid paths - should pass
       if(     !current.isValid("http://www.amazon.com/") ||
               !current.isValid("http://www.amazon.com/example/") ||
               !current.isValid("http://www.amazon.com/example")){


               System.out.println("Port Partition Test Failed! Valid ports identified as invalid");

       }
	else{

            	System.out.println("Port Partition Test Passed! Valid ports correctly identified as valid");

       }

	//3 invalid paths - should fail
       if(     current.isValid("http://www.amazon.com//badpath//") ||
               current.isValid("http://www.amazon.com/..") ||
               current.isValid("http://www.amazon.com///badpath")){


               System.out.println("Port Partition Test Failed! Invalid ports identified as valid");

       }


	else{

            	System.out.println("Port Partition Test Passed! Invalid ports correctly identified as invalid");

      	}

  } 
   
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.printf("\n\n--Combinatorial Testing--\n");
    //Create cover array which covers all 2-pair interactions
    //Means (0,0), (0,1), (1,0), and (1,1) for all ab, ac, ad ...de
    int[][] coverArray = {  
              { 0, 0, 0, 0, 0},
							{ 0, 0, 0, 0, 1},
							{ 0, 0, 1, 1, 0},
							{ 0, 1, 0, 0 ,1},
							{ 0, 1, 1, 0, 1},
							{ 0, 1, 1, 1, 1},
							{ 1, 0, 0, 1, 0},
							{ 1, 1, 0, 0, 0},
							{ 1, 0, 0, 0, 0},
							{ 1, 1, 0, 0, 1},
							{ 1, 1, 1, 1, 1},
              { 2, 2, 2, 2, 2},
              { 2, 2, 2, 2, 3},
              { 2, 2, 3, 3, 2},
              { 2, 3, 2, 2 ,3},
              { 2, 3, 3, 2, 3},
              { 2, 3, 3, 3, 3},
              { 3, 2, 2, 3, 2},
              { 3, 3, 2, 2, 2},
              { 3, 2, 2, 2, 2},
              { 3, 3, 2, 2, 3},
              { 3, 3, 3, 3, 3}
						};
	//build string to test url from above coverArray
	
	
    boolean printStatus=true;
	int statusPerLine = 60;
    int printed = 0;
    if (printIndex)  {
      statusPerLine = 6;
    }

	
	for(int coverIndex = 0; coverIndex < 22; coverIndex++){
		boolean expected = true;
		StringBuffer  testUrl = new StringBuffer();
		StringBuffer testBools = new StringBuffer();
		testBools.append("(");

		int[] indexList = coverArray[coverIndex];
		System.out.printf("Test "+ coverIndex + "\n\n");
		for(int count = 0; count< 5; count++){
			
			ResultPair[] part = (ResultPair[]) testUrlParts[count];
			testUrl.append(part[indexList[count]].item);
			System.out.printf("Part:" + part[indexList[count]].item + "  Valid:" + part[indexList[count]].valid + "\n");
			if(part[indexList[count]].valid == false){
				expected = false;
				testBools.append(" False ");
			} else {
				testBools.append(" True ");
			}
		}	

		testBools.append(")");

		String url = testUrl.toString();
		boolean result = urlVal.isValid(url);
		
		System.out.printf("Tested Url: " + url + "\n");
		System.out.printf("\nExpected: " + expected + "\n");
		System.out.printf("Result: " + result + "\n");
		
         //assertEquals(url, expected, result);
         
         if (printStatus) {
            if (printIndex) {
               //System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
               System.out.printf("\n\n");
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }

	}
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   //For the following result pairs, index 0 and evens will point to "false" option, odds to "true"
    ResultPair[] testUrlScheme = { new ResultPair("http:/", false),
                                   new ResultPair("http://", true),
                                   new ResultPair("hft:/", false),
                                   new ResultPair("ftp://", true)                              
    };
    ResultPair[] testUrlAuthority = {new ResultPair("goo.gle.com", false),
                                  new ResultPair("www.google.com", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.255.255.255", true)                                                         
    };
    ResultPair[] testUrlPort = { new ResultPair(":-1", false),
                               new ResultPair(":80", true),
                               new ResultPair(":900000", false),
                               new ResultPair(":65534", true)                            
    };
    ResultPair[] testPath = {new ResultPair("/..", false),
                          new ResultPair("/test1/", true),
                          new ResultPair(".//.", false),
                          new ResultPair("", true)                     
    };
    ResultPair[] testUrlQuery = {new ResultPair("?-1", false),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("???", false),
                              new ResultPair("", true)                         
    };
    Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};

}
