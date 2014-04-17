package com.ire.major;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;


public class Utility {
	private static BufferedReader br;
	
	static HashSet<String> stopWords = new HashSet<String>(Arrays.asList("thing","need","thats","using","said", 
			"particular","until","becoming","thanks","over","thereby","she","something","right", "these","else",
			"once","respectively","he","theirs","apart","few","further","herself", "downwards","somebody","each",
			"wherever","go","before","accordingly","indicate","namely", "six","hereafter","could","consider",
			"usually","tell","do","whither","thorough","f", "g","ex","d","may","e","b","noone","c",
			"needs","a","n","o","l","m","j","ones","k","h","i", "yes","service","w","ref","v","eg","u","new","t","s",
			"what","r","q","p","nothing","having","et","z", "y","yet","x","thru","anywhere","least","took",
			"by","enough","same","has","who","would", "any","everybody","overall","had","be","think","get",
			"seeing","likely","far","much","and", "co","particularly","gotten","near","better","often","against",
			"doing","containing","seeming", "example","does","ignored","saying","tried","former","through",
			"following","possible", "especially","name","tries","edu","all","keeps","five","obviously","at","as",
			"still", "therefore","hello","neither","never","which","see","take","anyone","am","there","an", "off",
			"thoroughly","why","they","nobody","somehow","no","nine","otherwise","anyways", "of","help","given",
			"among","anybody","on","only","says","her","ok","everyone","itself", "nbsp","oh","maybe","or","done",
			"regarding","third","sensible","category","them","then","book", "will","ought","furthermore","novel","upon",
			"different","indeed","getting","most","thanx", "followed","aside","across","looking","thank","normally",
			"unless","rather","me","kept","my", "whereupon","okay","delivery","specified","per","nd","sometime","within",
			"thereupon","described","truly", "follows","cause","tends","last","second","sometimes","being","contains",
			"him","actually", "since","where","every","eight","almost","unto","looks","more","his","inc","when",
			"someone", "wonder","value","useful","none","certainly","seriously","everywhere","asking","onto",
			"appropriate","such","hers","liked","whereafter","here","whole","this","causes","appreciate", 
			"becomes","way","hi","from","believe","while","was","allows","able","if","corresponding","ie", 
			"seemed","below","various","wherein","lest","between","less","those","is","besides","ourselves",
			"gives","your","gets","into","howbeit","in","know","two","away","necessary","themselves", "also",
			"changes","appear","etc","they'll","hopefully","ours","its","yourselves","exactly", "although",
			"formerly","greetings","entirely","along","secondly","alone","serious","awfully", "going",
			"nowhere","relatively","how","under","available","became","always","indicated", "theres",
			"inward","own","specify","indicates","try","we","reasonably","specifying","next", "use","hardly",
			"vs","consequently","whenever","best","mostly","definitely","unfortunately", "whatever","later",
			"come","us","seen","un","cannot","seem","up","math","either","insofar", "sorry","they'd","down",
			"happens","keep","to","com","both","inner","uucp","become", "somewhere","must","th","after",
			"nevertheless","whereby","considering","taken","welcome", "however","whose","so","behind","gone",
			"willing","whereas","that","associated","than", "whom","unlikely","thence","several","got","ltd",
			"hereby","sub","can","about","well","sup", "re","rd","above","que","four","qv","placed","too","yours",
			"thus","moreover","provides", "you","soon","immediate","anything","seven","whoever","certain","somewhat",
			"our","brief", "very","out","forth","via","hereupon","for","everything","towards","zero","whether",
			"went", "elsewhere","beyond","course","whence","are","yourself","therein","thereafter","plus", "others",
			"mainly","viz","did","again","like","without","non","shall","many","not","nor", "anyhow","cant","now",
			"say","myself","saw","ask","some","outside","might","self","trying", "they've","according","seems",
			"twice","latter","presumably","inasmuch","probably","want", "regardless","hence","just","fifth","let",
			"already","should","really","beforehand","clearly", "despite","hither","but","old","afterwards","meanwhile","wish",
			"herein","amongst","little", "used","together","though","been","anyway","were","sent","please","toward",
			"there's","three", "concerning","sure","throughout","goes","except","regards","comes","wants","himself",
			"knows", "contain","even","latterly","known","perhaps","ever","other","allow","have","one","selves", 
			"currently","merely","because","another","during","lately","mean","they're","with","nearly", "the","came",
			"around","beside","quite","instead","uses","their","first","lappy","acer","laptop","packing","experience",
			"products","product","books","laptop","questions","job","pleasure","problem","defects","defect","bit","dont",
			"issues","issue","years","year","things","thing","brother","cousin","compartments","compartment","its",
			"delivered","flipkart","place","copy","services","algo","book.delivery","turnaround","dude",
			"pm","lot","part","videos","time","person","books.i","becuase","tag","ther","!!!","people","eyes","authors",
			"luk","abt","thng","potter","heart","problems","waiting","krish","rockssssss","review","idea","choice","line",
			"states","caste","site.nobody","highly","life","emphasis","movie","!!","confidence","works","relationship","point",
			"route","teenagers","mixture","dishes","novels","world","blockbuster","reading","tooo","story.an","chetan","love",
			"bhagat","taunting","student","family","writer","work","da","situations","fan","ago.felt","stories","reader","day",
			"ride","attempt","result","concept","war","chapter","details","dis","bone","ddlj","readers","ji","manner","night",
			"detail","moves","chanakya","story","deal","avenues","facts","page","mixing","portrayal","perspective.must","piece",
			"ages","work","thoughts","turner","exponent","offers","journey","sense","mahabharata","stories","wont","areas","day",
			"laziness","events","ignorance","era","worlds","mishra","times","side","chant","couple","mind","ability","days.but",
			"twists","strategy","plots","library","manner","world","christians.but","chapters","novel.it","courage","code","hunt",
			"langdon","comeback","superb","breakdown","discount","model","plastic","concern","purchase","trouble","deal","shortcoming","shops",
			"packaging","dad","gen","machine","laptops","movie","machine","finish","system","drawback","cd","user","flaws","story.thats","mistakes",
			"past.really","contratry","kind","version","politician","author","deleivery","india","man","profs","condition","cart","customers","end.go",
			"institute","gadgets","half","store","iam","tabletes","combat","winner","deliverance","gb","search","generation","option","nexus","pricing",
			"tablet","devices","introduction","buddy","simple","downloads","originality","shutdown","cons","site","seceond","seller","selection","weeks",
			"sums","saturation","con","drop","good","genration","deal","bang","alternative","responce","upgrade","10k","case","shopping","specs","update",
			"set","purchase","complaints","response","hrs","kart","companion","feel","sites","apps","regret","persons","months","tablet","charge","effect",
			"device","usage","core","google","recharging","concern","tab","buying","guys","quality.this","portals","whit","buyer","usuage","holes","kat","support",
			"table","health","simplicity","stars","prize","pc","month","range","aspects","purposes","space","brands","display.i","mini","app","gamers",
			"corner","vendor","gues","htat","e-techies","account","brand","tabs","users","buy","wise","pack","product.its","disc","beast","shipping","applications",
			"saturday","flaw","reviews","gadget","doubt","class","market","stuff","release","movies","ease","state","excellent","pads","luks","couple","response.runs",
			"tasks","instrument","section","manual","specification","rating","user","kudos","technology.i","angles","deal","callinsystemis","loads","impression","sr","!!!!",
			"items","view","brand.in","data","purpose","network","hand","order","length","bettery","modems","playtime","play","lava","week","phone","lenovo","sum",
			"phones","khas","drive","guard","money","pros","longivity","angle","classes","edition","softwares","status","studies","points","topics","comers","areas",
			"ive","topics.i","reveal","brown","info","dip","fine.though","pages.i","end","teachings","symbol","research","masterpiece","rather.it",
			"friend","read.thought","coz","clifton","incidents","chronicles","interest","hary","bucks","series","episode","saga","collection","child","identity","storyteller",
			"evening","this.i","page.if","master","point","approach","archer","waste","atleast","phone","handset","backdrop","eyes","security.overall","features",
			"phn","5-supports","feature","working","support","lack","models","galaxy","mobile","phones","always.but","disadvantage","initially","numbers",
			"wen","samsung","bcoz","inch","ull","dnt","one.camera","ice-creame","software","i8552","mob","quattro","canvas","fone","great","duos","options",
			"buyers","back","offer","days","day","box","??","shatter","chance","customer","setback","ladies","run2","pc.it","decision","ve","restart","bean","overview",
			"awsome","lumia","nice","android","demerit","lag","yaar.flipkart","talk","application","im","football","drops","sound.sometimes","experiences","cracker","scientist",
			"episodes","bomb","volume","opinions","treasure.its","change","enlightment","doesnt","fable","impact","lesson","paulo","conspires","shepard","universe","forces","omens",
			"closets","nonsense.feels","gift","moment","consultancy","talent","calling","purpose","collection","kind","mirror","times","tale","treasure","quote","santiago","path",
			"feel","completed","pages","meaning","shepherd","turners","creations","morals","truths","storytelling","skill","parts","shiva","wait","flow","nature","interest","boring",
			"role","quantity","turn","ends","isnt","sequel","content","cities","ending","evry1","tripathy","senses","excitement","god","acts","saga","imagination","honestly","finale",
			"scenes","worker","quencher","ability","mahabharat","spirits","trust","material","standards","history","fact","arguments","pattern","feeling","hype","respect","edition",
			"taste","amount","friends","stuufs","consequence","immortals","belief","effort","enmy","installments","finish","amish","kudos","expectation","land","storyline","promise",
			"upto","cry","dimension","views","asthra","two-just","approach","skills","expectations","dint","problems","skill","start","thinking","decisions","mans","scene","conclusion",
			"evil","creation","segments","subject","thought","india","twisting","sequences","oath","links","twist","resemblance","twon","concerns","credit","visuals","spell",
			"connection","legends.but","sense","stuff","treat","concept","scope","loss","boredom","turns","deities","ebook","standard","website","expierince","conversations","concepts",
			"pass","asusual","couldnt","countries","references","threads","key","groups","research.kudos","symbol","lines","societies","ll","haigins","chant","religions","mind",
			"documents","buildup","drag","track","source","timelines","justice","bookmark","sheldon","scientists","problm","statements","opportunities","learner","return",
			"companies","list","variety","starter","practice","developer","company","base","revisions","lessons","glue","boy","lad","dslr","photography","function","camera.i",
			"pics","approx","title","level","results","debate","!!!!!","kit","mail","600D","comparison","alternatives","good.i","gifts","clearty","cheep","payment","watch",
			"number","pic","moments","xtra","friendly","pouch","seconds","features.anyone","clarity","pix","l28","limit","bokeh","study","deals","close","d-slr","d3100",
			"comments","occasions","one.now","days.it","haf","survey","completely","quickly.drivers","fine","worth","advantage","this.its","lapi","item","stores","technology",
			"keys","developers","comparison","process","area","havent","replacement","window","gpu","surprises","substitute","reasons","z30","battle","room","microprocessors",
			"nokia","mp","product.delivery","ko","fones","lane","failure","recharge","color","****","specced","suits","indians","cake","18k","neo","mtk","home","14k","phone.it",
			"mobiles","mah","places","size.camera","variant","switch","center","sight","opus","gaes","english","competition","rate","manufacturer","asus","town",
			"management","ipad","solution","feather","scheme","locations","exchange","impressions","articles","alternate","+","tablets","pieces","pocket","apple","5k","competitor",
			"realy","stock","file","donot","asphalt","hours","rupee","flip-kart","low","16000","blower","handet","centers","motorola","date","kot","repelling","downside","post",
			"crystal","ringtones","spot?i","runs","location","type","Motog","count","scores","cellphone","inthis","worthy","rocks","cash","suggestion","sms","combo","didnt","online",
			"panels","slot","rocks","updates","iphone","worry","fon","cum","apprehensive","awesome","respond","black","becz","floor","spec","smooth","run","lasts","preferences","files",
			"rates","hour","lagging","520","download","difficulty","fortune","contacts","shots","sets","gifted","freaky","portal","releases","int","difference","commendable","office",
			"functions","updates","expirence","frm","irritations","phne","average"));
	/*Anusha's Part Starting (only filetoarray included)*/
	public static ArrayList<String> filetoarray(String productname)
	  {
		  //read file and store in array & return it
		  try
		  {
			  ArrayList<String> result =new ArrayList<String>();
			  String filesFolder="D:\\NEW\\ProductReviewSummarisation\\src\\com\\ire\\major\\reviews\\Laptops\\";
			  File temp = new File(filesFolder+productname.trim());
			  
			  if(temp.exists())
			  {
				
				  br=new BufferedReader(new FileReader(temp));
				  productname= productname.replace("/","x");
				  productname= productname.replace("*","x");
				  productname= productname.replace(".","x");
					
				// BufferedReader br = new BufferedReader(new FileReader("./reviews/"+productname.trim()));
				 String line=null;
				 int lineno=0;
				 Boolean flag=false;
				 String []st = null;
				 while((line=br.readLine())!=null)
				  {
					 lineno++;
					 if(lineno==1)
					 {
						st = line.split("@@@");
						System.out.println(st[0].trim());
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
			  }
	
				 return result; 
		  }
		  catch(IOException e)
		  {
			  e.printStackTrace();
			  return null;
		  }
	  
	  } 
	/* Anusha's Part Ending*/
	
}

