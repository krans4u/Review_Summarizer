package com.ire.major;



public class PolarityDetection {

	

	public static String getPolarity(double totalScore) {
	
	    String polarity = "";               
	    if(totalScore>0.75)
	    	polarity = "strong_positive";
	    else if(totalScore > 0.25 && totalScore<=0.75)
	    	polarity = "positive";
	    else if(totalScore > 0 && totalScore<=0.25)
	    	polarity = "weak_positive";
	    else if(totalScore < 0 && totalScore>=-0.25)
	    	polarity = "weak_negative";
	    else if(totalScore < -0.25 && totalScore>=-0.75)
	    	polarity = "negative";
	    else if(totalScore<-0.75)
	    	polarity = "strong_negative";
		return polarity;
	}

	public static double getScore(String o) {
		
		SentiWordNet test = new SentiWordNet();
	    String sentence=o;
	    String[] words = sentence.split("\\s+"); 
	    double totalScore = 0;
	    for(String word : words) {
	        word = word.replaceAll("([^a-zA-Z\\s])", "");
	        if (test.extract(word) == null)
	            continue;
	        totalScore += test.extract(word);
	    }
	    return totalScore;
	}
	/*public HashMap<String, HashMap<String,ArrayList<Integer>>> opinionWordsExtraction(HashMap<Integer, ArrayList<String>> map, ArrayList<String> list) {

		//System.out.println("IN OPINION");
		HashMap<String, HashMap<String,ArrayList<Integer>>> finalList= new HashMap<String, HashMap<String,ArrayList<Integer>>>();
		for (int reviewIndex = 0; reviewIndex < list.size(); reviewIndex++) {

			ArrayList<HashMap<Integer, OpinionList>> subReviewsAdjList = new ArrayList<HashMap<Integer, OpinionList>>();
			ArrayList<HashMap<Integer, String>> subReviewsFeatureList = new ArrayList<HashMap<Integer, String>>();
			String words[] = list.get(reviewIndex).trim().split(" ");
			ArrayList<String> productFeatures = map.get(reviewIndex);
			int featureIndex = 0;
			int subReviewIndex=0;
			int wordCurrentIndex = 0;
			int wordIndex=0;
			int flag=0;
			while (true) {
				if(wordCurrentIndex==words.length) { 
					break;
				}
				flag=0;
				HashMap<Integer, OpinionList> map1 = new HashMap<Integer, OpinionList>();
				HashMap<Integer, String> map2 = new HashMap<Integer, String>();
				for (wordIndex = wordCurrentIndex; wordIndex < words.length; wordIndex++) {
					
					if (words[wordIndex].contains("/JJ")) {

						OpinionList ol=new OpinionList();
						ol.setOpinionWord(words[wordIndex].substring(0, words[wordIndex].indexOf("/")));
						ol.setStatus(false);
						map1.put(wordIndex,ol);

					} else if((featureIndex!=productFeatures.size()) && (words[wordIndex].substring(0, words[wordIndex].indexOf("/")).equalsIgnoreCase(productFeatures.get(featureIndex)))) {

						map2.put(wordIndex,productFeatures.get(featureIndex));
						featureIndex++;

					} else if(words[wordIndex].equals("./.") || words[wordIndex].equals(",/,")) {
						subReviewIndex++;
						wordCurrentIndex = ++wordIndex;
						flag=1;
						break;
					}
				}
				if(flag==0)
				{
					subReviewIndex++;
					wordCurrentIndex = wordIndex;
				}
				subReviewsAdjList.add(map1);
				subReviewsFeatureList.add(map2);
			}
			
			for(int i=0;i<subReviewIndex;i++)
			{
				HashMap<Integer, OpinionList> map1 = subReviewsAdjList.get(i);
				HashMap<Integer, String> map2 =subReviewsFeatureList.get(i);
				if((map1.size()==0) || (map2.size()==0))
				{
					continue;
				}
				Iterator<Entry<Integer, OpinionList>> it1= map1.entrySet().iterator();
				Iterator<Entry<Integer, String>> it2=map2.entrySet().iterator();
				
				int currentIndex1=0;
				OpinionList currentOl = null;
				int currentIndex2=0;
				OpinionList currentO2 = null;
				
				if(it1.hasNext())
				{
					Map.Entry<Integer, OpinionList> pairs1 = (Map.Entry<Integer, OpinionList>)it1.next();
					currentIndex1=(int) pairs1.getKey();
					currentOl=pairs1.getValue();
				}
				if(it1.hasNext())
				{
					Map.Entry<Integer, OpinionList> pairs1 = (Map.Entry<Integer, OpinionList>)it1.next();
					currentIndex2=(int) pairs1.getKey();
					currentO2=pairs1.getValue();
				}
				
				while(it2.hasNext())
				{
					Map.Entry<Integer, String> pairs2 = (Map.Entry<Integer, String>)it2.next();
					int index2= (int) pairs2.getKey();
					String feature = pairs2.getValue();
					if(currentO2!=null)
					{
						if((currentIndex1<index2) && (currentIndex2<index2))
						{
							while(it1.hasNext() && (((currentIndex1<index2) && (currentIndex2>index2)) ) )
							{
								currentIndex1=currentIndex2;
								currentOl=currentO2;
								Map.Entry<Integer, OpinionList> pairs1 = (Map.Entry<Integer, OpinionList>)it1.next();
								currentIndex2=(int) pairs1.getKey();
								currentO2=pairs1.getValue();
							}
							if(!((currentIndex1<index2) && (currentIndex2>index2)))
							{
								currentIndex1=currentIndex2;
								currentOl=currentO2;
							}
						}
						else
						{
							//assign current1 to quality
							if(!finalList.containsKey(feature))
							{
								HashMap<String, ArrayList<Integer>> newList= new HashMap<String, ArrayList<Integer>>();
								ArrayList<Integer> arrayList= new ArrayList<Integer>();
								arrayList.add(reviewIndex+1);
								newList.put(currentOl.getOpinionWord(),arrayList );
								finalList.put(feature, newList);
							}
							else
							{
								HashMap<String, ArrayList<Integer>> oldList= finalList.get(feature);
								if(oldList.containsKey(currentOl.getOpinionWord()))
								{
									ArrayList<Integer> arrayList= oldList.get(currentOl.getOpinionWord());
									arrayList.add(reviewIndex);
								}
								else
								{
									ArrayList<Integer> arrayList= new ArrayList<Integer>();
									arrayList.add(reviewIndex);
									oldList.put(currentOl.getOpinionWord(),arrayList );
								}
							}
							
						}
						if((index2>currentIndex1) && (currentOl.getStatus()==false))
						{
							// assign the current1 to quality
							if(!finalList.containsKey(feature))
							{
								HashMap<String, ArrayList<Integer>> newList= new HashMap<String, ArrayList<Integer>>();
								ArrayList<Integer> arrayList= new ArrayList<Integer>();
								arrayList.add(reviewIndex+1);
								newList.put(currentOl.getOpinionWord(),arrayList );
								finalList.put(feature, newList);
							}
							else
							{
								HashMap<String, ArrayList<Integer>> oldList= finalList.get(feature);
								if(oldList.containsKey(currentOl.getOpinionWord()))
								{
									ArrayList<Integer> arrayList= oldList.get(currentOl.getOpinionWord());
									arrayList.add(reviewIndex);
								}
								else
								{
									ArrayList<Integer> arrayList= new ArrayList<Integer>();
									arrayList.add(reviewIndex);
									oldList.put(currentOl.getOpinionWord(),arrayList );
								}
							}
							
						}
						else if((index2>currentIndex1) && (currentOl.getStatus()==true))
						{
							if((!it1.hasNext()) && (!it2.hasNext()))
							{
								// assign current1 to quality
								if(!finalList.containsKey(feature))
								{
									HashMap<String, ArrayList<Integer>> newList= new HashMap<String, ArrayList<Integer>>();
									ArrayList<Integer> arrayList= new ArrayList<Integer>();
									arrayList.add(reviewIndex+1);
									newList.put(currentOl.getOpinionWord(),arrayList );
									finalList.put(feature, newList);
								}
								else
								{
									HashMap<String, ArrayList<Integer>> oldList= finalList.get(feature);
									if(oldList.containsKey(currentOl.getOpinionWord()))
									{
										ArrayList<Integer> arrayList= oldList.get(currentOl.getOpinionWord());
										arrayList.add(reviewIndex);
									}
									else
									{
										ArrayList<Integer> arrayList= new ArrayList<Integer>();
										arrayList.add(reviewIndex);
										oldList.put(currentOl.getOpinionWord(),arrayList );
									}
								}
							}
							else
							{
								
								// assign current2 to quality
								if(!finalList.containsKey(feature))
								{
									HashMap<String, ArrayList<Integer>> newList= new HashMap<String, ArrayList<Integer>>();
									ArrayList<Integer> arrayList= new ArrayList<Integer>();
									arrayList.add(reviewIndex+1);
									newList.put(currentO2.getOpinionWord(),arrayList );
									finalList.put(feature, newList);
								}
								else
								{
									HashMap<String, ArrayList<Integer>> oldList= finalList.get(feature);
									if(oldList.containsKey(currentO2.getOpinionWord()))
									{
										ArrayList<Integer> arrayList= oldList.get(currentO2.getOpinionWord());
										arrayList.add(reviewIndex);
									}
									else
									{
										ArrayList<Integer> arrayList= new ArrayList<Integer>();
										arrayList.add(reviewIndex);
										oldList.put(currentO2.getOpinionWord(),arrayList );
									}
								}
								
							}
							

							currentIndex1=currentIndex2;
							currentOl=currentO2;
							currentIndex2=0;
							currentO2=null;
							if(it1.hasNext())
							{
								Map.Entry<Integer, OpinionList> pairs1 = (Map.Entry<Integer, OpinionList>)it1.next();
								currentIndex2=(int) pairs1.getKey();
								currentO2=pairs1.getValue();
							}
						}
					}
					else
					{
						// assign one feature to quality
						if(!finalList.containsKey(feature))
						{
							HashMap<String, ArrayList<Integer>> newList= new HashMap<String, ArrayList<Integer>>();
							ArrayList<Integer> arrayList= new ArrayList<Integer>();
							arrayList.add(reviewIndex+1);
							newList.put(currentOl.getOpinionWord(),arrayList );
							finalList.put(feature, newList);
						}
						else
						{
							HashMap<String, ArrayList<Integer>> oldList= finalList.get(feature);
							if(oldList.containsKey(currentOl.getOpinionWord()))
							{
								ArrayList<Integer> arrayList= oldList.get(currentOl.getOpinionWord());
								arrayList.add(reviewIndex);
							}
							else
							{
								ArrayList<Integer> arrayList= new ArrayList<Integer>();
								arrayList.add(reviewIndex);
								oldList.put(currentOl.getOpinionWord(),arrayList );
							}
						}
					}
				}
				
			}
		}
		
		return finalList;
	}*/

}
