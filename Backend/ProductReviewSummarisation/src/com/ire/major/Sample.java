package com.ire.major;
 
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.SocketTimeoutException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.StringTokenizer;
 
import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Sample{
	 
	static HashMap<String,Boolean> hm = new HashMap<String,Boolean>();
	static HashSet<String> allLinks = new HashSet<String>();
	static int funcount=0;

	static Document doc;
	public static void main(String[] args) {

	
	try {
		
			Crawl c=new Crawl();
			//c.filetoarray("Introduction To Algorithms 3rd Edition ");
			BufferedReader br = null;
			 
			//ArrayList<String> result = new ArrayList<String>();
			System.setProperty("http.proxyHost", "proxy.iiit.ac.in");
			System.setProperty("http.proxyPort", "8080");	
			String noofreviews="";
			
			File folder = new File("C:/Users/user/Desktop/flipkart/");
			File[] listOfFiles = folder.listFiles();
			String line="";
			for (int i = 0; i < listOfFiles.length; i++) {
			  File file = listOfFiles[i];
			  if (file.isFile())
			  {
				  
				  br = new BufferedReader(new FileReader(file));
				  //for all urls in dat file
				  int noOfPages=0;
				  Sample.allLinks.clear();
				  Sample.hm.clear();
				  
				  while ((line= br.readLine()) != null) {
						System.out.println(line);
						
						Sample.doc=null;
						try{
							doc=Jsoup.connect(line).get();
						}
						catch(Exception e){
							//e.printStackTrace();
							System.out.println("Invalid URL in file");
							continue;
						}
						
						Elements name=doc.getElementsByTag("h1");
						String title="";
						for(Element head:name)
						{
							title = head.text();
						}
						Elements links = doc.select("a[href]");
						String absHref="";
						for (Element link : links) {
							if(link.attr("href").equals("#read-reviews"))
							{
								absHref= link.attr("abs:href");
								noofreviews=link.text();
								noOfPages = Integer.parseInt(noofreviews.split(" ")[0]);
								System.out.println("....no of reviews "+noofreviews);
								doc=Jsoup.connect(absHref).get();
								break;
								
							}
				 
						}
						Elements link_nextr= doc.select("a");
						
						  for(Element link:link_nextr)
						  {
							  if(link.text().trim().equalsIgnoreCase("read all reviews"))
							  {
								 
								  absHref = link.attr("abs:href");
								  //System.out.println("==================="+absHref);
							//	  funcount++;
								 getAllReviews(absHref, (noOfPages+9)/10, title);
								  break;
								  }
							  }
					  
						funcount=0;  
					}
				  
				  
			  }
			 
			}
			
		
		
	
		} catch (Exception e) {
			//e.printStackTrace();
		}
	 
	  }
	private static void getAllReviews(String absHref, int i, String title) {
		String url ;
		Crawl c = new Crawl();
		for(int u=0;u<i;u++){
			url = absHref+"&start="+(u*10);
			funcount++;
			c.reviewstore(url, title);
			//System.out.println("visited page "+u);
		}
		
	}
	  
	}
	  class Crawl
	  {
		
	  public void reviewstore(String absHref,String title)
	  {
		 
		  try
		  {
			  title = title.replace("/","x");
			  title = title.replace("*","x");
			  title = title.replace(".","x");
			  FileWriter fw = new FileWriter("D:/NEW/ProductReviewSummarisation/src/com/ire/major/reviews/Tablets/"+title,true);
		      PrintWriter pw = new PrintWriter(fw);
			  if(Sample.funcount==1)
			  {
				  pw.append(title);
				  pw.append("@@@");
			  }
			  Sample.doc=Jsoup.connect(absHref).get();
			 Elements divs=Sample.doc.select("div[class=lastUnit size4of5 section2]");
			 for(Element para :divs)
			  {
				
				if(para.children().select("p")!=null)
				{
				 pw.append(para.children().select("p").text());
				  pw.append("\n");
			  }
			  }
			  absHref="";
			  pw.close();
	  }
	  catch(IOException e)
	  {
		//	e.printStackTrace();
	  }
  }
  
  
	  
	  
	  public ArrayList<String> filetoarray(String productname)
	  {
		  //read csv file and store in array & return it
		  try
		  {
		  			
				  productname= productname.replace("/","x");
				  productname= productname.replace("*","x");
				  productname= productname.replace(".","x");
					
				  BufferedReader br = new BufferedReader(new FileReader("./reviews/"+productname.trim()));
				 String line=null;
				 ArrayList<String> result =new ArrayList<String>();
				 int lineno=0;
				 Boolean flag=false;
				 String []st = null;
				 while((line=br.readLine())!=null)
				  {
					 lineno++;
					 if(lineno==1)
					 {
						st = line.split("@@@");
							if(st[0].trim().equalsIgnoreCase(productname.trim()))
							{
								
								flag=true;
							
							}
							if(flag!=true)
							{
								System.out.println("given product is not valid");
								break;
							}
							if(flag==true)
							{
							result.add(st[1]);
							}
						
					 }
					 else
					 {
						 result.add(line);
					 }
				  }
				 
				 br.close();
				 return result;
		  }
		  catch(IOException e)
		  {
			  e.printStackTrace();
			  return null;
		  }
	  
	  }//close filetoarray  
	  
  
 
  
  
  
  }

