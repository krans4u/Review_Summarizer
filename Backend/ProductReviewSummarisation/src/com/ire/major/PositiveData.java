package com.ire.major;

public class PositiveData extends ReviewData{

	int positiveReviewCount;
	ReviewScore r1;
	ReviewScore r2;
	public int getPositiveReviewCount() {
		return positiveReviewCount;
	}
	public void setPositiveReviewCount(int positiveReviewCount) {
		this.positiveReviewCount = positiveReviewCount;
	}
	public ReviewScore getR1() {
		return r1;
	}
	public void setR1(ReviewScore r1) {
		this.r1 = r1;
	}
	public ReviewScore getR2() {
		return r2;
	}
	public void setR2(ReviewScore r2) {
		this.r2 = r2;
	}
	
}
