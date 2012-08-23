Getwordsearches::Application.routes.draw do
  get "word_search/index"

  get "word_search/view"

  post "word_search/create"

  get "word_search/new"

  # You can have the root of your site routed with "root"
  # just remember to delete public/index.html.
	root :to => 'landing_page#index'

  # See how all your routes lay out with "rake routes"

  # This is a legacy wild controller route that's not recommended for RESTful applications.
  # Note: This route will make all actions in every controller accessible via GET requests.
  # match ':controller(/:action(/:id))(.:format)'
end
