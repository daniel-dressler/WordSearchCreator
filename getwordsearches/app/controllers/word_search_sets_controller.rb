
class WordSearchSetsController < ApplicationController
  	# GET /word_search_sets
  	# GET /word_search_sets.json
  	def index
    	@word_search_sets = WordSearchSet.all

    	respond_to do |format|
      		format.html # index.html.erb
      		format.json { render json: @word_search_sets }
    	end
  	end

  	# GET /word_search_sets/1
  	# GET /word_search_sets/1.json
  	def show
    	@word_search_set = WordSearchSet.find(params[:id])

    	respond_to do |format|
      		format.html # show.html.erb
      		format.json { render json: @word_search_set }
    	end
  	end

  	# GET /word_search_sets/new
  	# GET /word_search_sets/new.json
  	def new
    	@word_search_set = WordSearchSet.new

    	respond_to do |format|
      		format.html # new.html.erb
      		format.json { render json: @word_search_set }
    	end
  	end

  	# GET /word_search_sets/1/edit
  	def edit
    	@word_search_set = WordSearchSet.find(params[:id])
  	end

  	# POST /word_search_sets
  	# POST /word_search_sets.json
  	def create
    	@word_search_set = WordSearchSet.new(params[:word_search_set])

    	respond_to do |format|
      		if @word_search_set.save
        		format.html { redirect_to @word_search_set, notice: 'Word search set was successfully created.' }
        		format.json { render json: @word_search_set, status: :created, location: @word_search_set }
      		else
        		format.html { render action: "new" }
        		format.json { render json: @word_search_set.errors, status: :unprocessable_entity }
      		end
    	end
  	end

  	# PUT /word_search_sets/1
  	# PUT /word_search_sets/1.json
  	def update
    	@word_search_set = WordSearchSet.find(params[:id])

    	respond_to do |format|
      		if @word_search_set.update_attributes(params[:word_search_set])
        		format.html { redirect_to @word_search_set, notice: 'Word search set was successfully updated.' }
        		format.json { head :no_content }
      		else
        		format.html { render action: "edit" }
        		format.json { render json: @word_search_set.errors, status: :unprocessable_entity }
      		end
    	end
  	end

  	# DELETE /word_search_sets/1
  	# DELETE /word_search_sets/1.json
  	def destroy
    	@word_search_set = WordSearchSet.find(params[:id])
    	@word_search_set.destroy

    	respond_to do |format|
      		format.html { redirect_to word_search_sets_url }
      		format.json { head :no_content }
    	end
  	end

  	def preview
	  	@word_search_set = WordSearchSet.new()
		@word_search_set.step1(1, params[:angles]);
	  	@word_search_set.step2(params[:words], params[:swears])
		@word_search_set.press
	  	render :template => 'word_search/view', :layout => 'basic'
  	end
end
