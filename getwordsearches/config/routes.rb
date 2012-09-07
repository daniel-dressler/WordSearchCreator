Getwordsearches::Application.routes.draw do
  	resources :word_search_sets

  	get "word_search/index"

  	match "preview/:angles/:words/:swears/:seed", :to => "word_search#preview"

  	get "word_search/view"

  	post "word_search/create"

  	get "word_search/new"
	
	root :to => 'landing_page#index'
end
