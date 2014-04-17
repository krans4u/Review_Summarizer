package com.ire.major;

import java.io.FileWriter;
import java.io.IOException;
import java.io.StringReader;
import java.util.*;
import org.json.JSONObject;
import edu.stanford.nlp.ling.*;
import edu.stanford.nlp.trees.*;
import edu.stanford.nlp.parser.lexparser.LexicalizedParser;
import edu.stanford.nlp.process.CoreLabelTokenFactory;
import edu.stanford.nlp.process.PTBTokenizer;
import edu.stanford.nlp.process.TokenizerFactory;


public class FeatureExtractionWithSentimentAnalysis {

	static int total;
	static Map<String,ReviewData []> finalSummaryResult= new HashMap<String, ReviewData []>();
	public static <E> void main(String[] args) throws Exception {
		
		ArrayList<String> list=Utility.filetoarray("Asus 1015E-CY041D Netbook (CDCx 2GBx 320GBx DOS)");
		LexicalizedParser lp = LexicalizedParser.loadModel("edu/stanford/nlp/models/lexparser/englishPCFG.ser.gz");
		lp.setOptionFlags(new String[]{"-maxLength", "80", "-retainTmpSubcategories"});
		
		System.out.println();
		TokenizerFactory<CoreLabel> tokenizerFactory = PTBTokenizer.factory(new CoreLabelTokenFactory(), "");

		Map<String,Integer> phraseList=new HashMap<String,Integer>();
		Map<Integer,ArrayList<String>> nouns= new HashMap<Integer, ArrayList<String>>(); 
		Map<Integer,ArrayList<String>> features= new HashMap<Integer, ArrayList<String>>(); 
		Map<Integer,ArrayList<String>> neg= new HashMap<Integer, ArrayList<String>>();
		Map<Integer,ArrayList<Amod>> amod= new HashMap<Integer, ArrayList<Amod>>();
		

		long t1= System.currentTimeMillis();
		for(int reviewIndex=0;reviewIndex<list.size();reviewIndex++)
		{
			List<CoreLabel> rawWords = tokenizerFactory.getTokenizer(new StringReader(list.get(reviewIndex))).tokenize();
			total=total+rawWords.size(); 
			Tree parse = lp.apply(rawWords);
			TreebankLanguagePack tlp = new PennTreebankLanguagePack();
			GrammaticalStructureFactory gsf = tlp.grammaticalStructureFactory();
			GrammaticalStructure gs = gsf.newGrammaticalStructure(parse);
			List<TypedDependency> tdl = gs.typedDependenciesCCprocessed();

			ArrayList<String> negReview=new ArrayList<String>();
			ArrayList<Amod> amodReview=new ArrayList<Amod>();
			ArrayList<String> nounReview= new ArrayList<String>();
			TreeSet<String> arr= findNoun(parse);
			TreeSet<String> arr1= findAdjective(parse);
			for(int index=0;index<tdl.size();index++)
			{
				String relation= tdl.get(index).reln().toString();
				if(relation.equals("nsubj") || relation.equals("dobj"))
				{

					Tree noun=tdl.get(index).dep();

					if(!Utility.stopWords.contains(noun.nodeString().toLowerCase()))
					{

						if(arr.contains(noun.nodeString()))
						{
							Tree firstPart= tdl.get(index).gov();

							Amod amodRelation=null;

							if(arr1.contains(firstPart.nodeString()))
							{
								amodRelation= new Amod();
								amodRelation.setNoun(noun.nodeString().toString());
								amodRelation.setAdjective(firstPart.nodeString().toString());
								amodReview.add(amodRelation);
							}

						}

						int count = phraseList.containsKey(noun.nodeString()) ? phraseList.get(noun.nodeString()) : 0;
						phraseList.put(noun.nodeString(), count + 1);
						if(!nounReview.contains(noun.nodeString().toString()))
						{
							nounReview.add(noun.nodeString().toString());
						}
					}
				}
				else if(relation.equals("neg"))
				{
					negReview.add(tdl.get(index).gov().toString());

				}
				else if(relation.equals("amod"))
				{
					Tree noun=tdl.get(index).gov();
					if(!Utility.stopWords.contains(noun.nodeString().toLowerCase()))
					{
						Amod amodRelation= new Amod();
						amodRelation.setNoun(tdl.get(index).gov().nodeString().toString());
						amodRelation.setAdjective(tdl.get(index).dep().nodeString().toString());
						amodReview.add(amodRelation);

						if(arr.contains(noun.nodeString()))
						{
							int count = phraseList.containsKey(noun.nodeString()) ? phraseList.get(noun.nodeString()) : 0;
							phraseList.put(noun.nodeString(), count + 1);
							if(!nounReview.contains(noun.nodeString().toString()))
							{
								nounReview.add(noun.nodeString().toString());
							}

						}
					}

				}

			}
			neg.put(reviewIndex, negReview);
			amod.put(reviewIndex, amodReview);
			nouns.put(reviewIndex, nounReview);

		}

		// Traverse the map nouns and make the map for features .

		for(int nounsIndex=0;nounsIndex< nouns.size();nounsIndex++)
		{
			ArrayList<String> nounReview= nouns.get(nounsIndex);
			ArrayList<String> featureReview= new ArrayList<String>();
			for(int nounReviewIndex=0;nounReviewIndex<nounReview.size();nounReviewIndex++)
			{
				String noun =nounReview.get(nounReviewIndex);

				if(noun.length()>2)
				{
					if(phraseList.containsKey(noun))
					{
						int nounCount= phraseList.get(noun);
						//double countScore= (nounCount/(double)total)*100;
						if(nounCount>=1)
						{
							featureReview.add(noun);
						}
					}
				}
				
			}
			features.put(nounsIndex, featureReview);
		}

		nouns.clear();

		/*long t2= System.currentTimeMillis();
		System.out.println("first: "+ (t2-t1));*/
		// Traverse the features map and get the associated opinion word

		//long t3= System.currentTimeMillis();
		for(int featureIndex=0;featureIndex<features.size();featureIndex++)
		{
			ArrayList<String> featureReview= features.get(featureIndex);
			ArrayList<Amod> amodReview= amod.get(featureIndex);
			ArrayList<String> negReview= neg.get(featureIndex);

			for(int featureReviewIndex=0;featureReviewIndex<featureReview.size();featureReviewIndex++)
			{
				double totalScore=0;
				String feature= featureReview.get(featureReviewIndex);
				for(int amodReviewIndex=0;amodReviewIndex<amodReview.size();amodReviewIndex++)
				{
					Amod a= amodReview.get(amodReviewIndex);
					if(feature.equalsIgnoreCase(a.getNoun()))
					{
						String opinionWord= a.getAdjective();
						double tempScore= PolarityDetection.getScore(opinionWord);
						if(negReview.contains(opinionWord))
						{
							tempScore= -tempScore;
						}

						totalScore+=totalScore+tempScore;

					}
				}
				// add the score of first three best review for the particular faeture for positive and negative

				String polarity= PolarityDetection.getPolarity(totalScore);
				if(polarity.contains("positive"))
				{
					if(finalSummaryResult.containsKey(feature))
					{
						ReviewData[] featureSummaryData= finalSummaryResult.get(feature);
						PositiveData positive= (PositiveData) featureSummaryData[0];
						if(positive!=null)
						{
							positive.setPositiveReviewCount(positive.getPositiveReviewCount()+1);
							ReviewScore r1=positive.getR1();
							ReviewScore r2=null;
							if(r1==null)
							{
								r1= new ReviewScore();
								r1.setReviewNumber(featureIndex);
								r1.setReviewScore(totalScore);
							}
							else
							{
								r2= positive.getR2();
								if(r2==null)
								{
									r2= new ReviewScore();
									if(r1.getReviewScore()>=totalScore)
									{
										r2.setReviewNumber(featureIndex);
										r2.setReviewScore(totalScore);
									}
									else
									{
										r2.setReviewNumber(r1.getReviewNumber());
										r2.setReviewScore(r1.getReviewScore());
										r1.setReviewNumber(featureIndex);
										r1.setReviewScore(totalScore);
									}
								}
								else
								{
									if(totalScore>r1.getReviewScore())
									{
										r2.setReviewNumber(r1.getReviewNumber());
										r2.setReviewScore(r1.getReviewScore());
										r1.setReviewNumber(featureIndex);
										r1.setReviewScore(totalScore);
									}
									else if((totalScore<r1.getReviewScore()) && (totalScore>r2.getReviewScore()))
									{
										r2.setReviewNumber(featureIndex);
										r2.setReviewScore(totalScore);
									}
								}
							}
							positive.setR1(r1);
							positive.setR2(r2);
						}
						else
						{
							positive= new PositiveData();
							ReviewScore r1= new ReviewScore();
							r1.setReviewNumber(featureIndex);
							r1.setReviewScore(totalScore);
							positive.setPositiveReviewCount(1);
							positive.setR1(r1);
							featureSummaryData[0]= positive;
						}

					}
					else
					{
						ReviewData[] featureSummaryData= new ReviewData[2];
						PositiveData positive= new PositiveData();
						ReviewScore r1= new ReviewScore();
						r1.setReviewNumber(featureIndex);
						r1.setReviewScore(totalScore);
						positive.setPositiveReviewCount(1);
						positive.setR1(r1);
						featureSummaryData[0]= positive;
						finalSummaryResult.put(feature, featureSummaryData);
					}
				}
				else if(polarity.contains("negative"))
				{
					if(finalSummaryResult.containsKey(feature))
					{
						ReviewData[] featureSummaryData= finalSummaryResult.get(feature);
						NegativeData negative= (NegativeData) featureSummaryData[1];

						if(negative!=null)
						{
							negative.setNegativeReviewCount(negative.getNegativeReviewCount()+1);
							ReviewScore r1=negative.getR1();
							ReviewScore r2=null;
							if(r1==null)
							{
								r1= new ReviewScore();
								r1.setReviewNumber(featureIndex);
								r1.setReviewScore(totalScore);
							}
							else
							{
								r2= negative.getR2();
								if(r2==null)
								{
									r2= new ReviewScore();
									if(r1.getReviewScore()>=totalScore)
									{
										r2.setReviewNumber(featureIndex);
										r2.setReviewScore(totalScore);
									}
									else
									{
										r2.setReviewNumber(r1.getReviewNumber());
										r2.setReviewScore(r1.getReviewScore());
										r1.setReviewNumber(featureIndex);
										r1.setReviewScore(totalScore);
									}
								}
								else
								{
									if(totalScore>r1.getReviewScore())
									{
										r2.setReviewNumber(r1.getReviewNumber());
										r2.setReviewScore(r1.getReviewScore());
										r1.setReviewNumber(featureIndex);
										r1.setReviewScore(totalScore);
									}
									else if((totalScore<r1.getReviewScore()) && (totalScore>r2.getReviewScore()))
									{
										r2.setReviewNumber(featureIndex);
										r2.setReviewScore(totalScore);
									}
								}
							}
							negative.setR1(r1);
							negative.setR2(r2);
						}
						else
						{
							negative= new NegativeData();
							ReviewScore r1= new ReviewScore();
							r1.setReviewNumber(featureIndex);
							r1.setReviewScore(totalScore);
							negative.setNegativeReviewCount(1);
							negative.setR1(r1);
							featureSummaryData[1]= negative;
						}

					}
					else
					{
						ReviewData[] featureSummaryData= new ReviewData[2];
						NegativeData negative= new NegativeData();
						ReviewScore r1= new ReviewScore();
						r1.setReviewNumber(featureIndex);
						r1.setReviewScore(totalScore);
						negative.setNegativeReviewCount(1);
						negative.setR1(r1);
						featureSummaryData[1]= negative;
						finalSummaryResult.put(feature, featureSummaryData);
					}
				}
			}


		}

		//long t4= System.currentTimeMillis();
		//System.out.println("second: "+(t4-t3));
		// print the finalSummaryResult
		JSONObject obj = new JSONObject();
		for(Map.Entry<String,ReviewData []> m: finalSummaryResult.entrySet())
		{
			//System.out.println(m.getKey()+":");
			JSONObject obj2 = new JSONObject();
			ReviewData[] featureSummaryData= m.getValue();
			PositiveData positive= (PositiveData) featureSummaryData[0];
			NegativeData negative= (NegativeData) featureSummaryData[1];
			if(positive!=null)
			{
				//System.out.println("Positive:"+positive.getPositiveReviewCount());
				obj2.put("positive",positive.getPositiveReviewCount());
				ReviewScore r1=positive.getR1();
				ReviewScore r2= positive.getR2();
				if(r1!=null)
				{
					obj2.put("posr1", list.get(r1.getReviewNumber()));
					//System.out.println(r1.reviewNumber+"	"+r1.reviewScore);
				}
				if(r2!=null)
				{
					obj2.put("posr2", list.get(r2.getReviewNumber()));
					//System.out.println(r2.reviewNumber+"	"+r2.reviewScore);
				}
			}
			if(negative!=null)
			{
				//System.out.println("Negative:"+negative.getNegativeReviewCount());
				obj2.put("negative",negative.getNegativeReviewCount());
				ReviewScore r3=negative.getR1();
				ReviewScore r4= negative.getR2();
				if(r3!=null)
				{
					obj2.put("negr1", list.get(r3.getReviewNumber()));
					//System.out.println(r3.reviewNumber+"	"+r3.reviewScore);
				}
				if(r4!=null)
				{
					obj2.put("negr2", list.get(r4.getReviewNumber()));
					//System.out.println(r4.reviewNumber+"	"+r4.reviewScore);
				}
			}
			obj.put(m.getKey(),obj2);
			try {

				FileWriter file = new FileWriter("D:/NEW/ProductReviewSummarisation/src/com/ire/major/Asus 1015E-CY041D Netbook (CDCx 2GBx 320GBx DOS).json");
				//System.out.println(obj.toString());
				file.write(obj.toString());
				file.flush();
				file.close();

			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	private static TreeSet<String> findNoun(Tree t) {
		TreeSet<String> nouns = new TreeSet<String>();
		if (t.label().value().equals("NN") || t.label().value().equals("NNS") || t.label().value().equals("NNP") || t.label().value().equals("NNPS"))
			nouns.add(t.getLeaves().get(0).toString());
		else
			for (Tree child : t.children())
				nouns.addAll(findNoun(child));
		return nouns;
	}

	private static TreeSet<String> findAdjective(Tree t) {
		TreeSet<String> adjectives = new TreeSet<String>();
		if (t.label().value().equals("JJ") || t.label().value().equals("JJR") || t.label().value().equals("JJS"))
			adjectives.add(t.getLeaves().get(0).toString());
		else
			for (Tree child : t.children())
				adjectives.addAll(findAdjective(child));
		return adjectives;
	}
}
