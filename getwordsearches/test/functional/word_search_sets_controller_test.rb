require 'test_helper'

class WordSearchSetsControllerTest < ActionController::TestCase
  setup do
    @word_search_set = word_search_sets(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:word_search_sets)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create word_search_set" do
    assert_difference('WordSearchSet.count') do
      post :create, word_search_set: {  }
    end

    assert_redirected_to word_search_set_path(assigns(:word_search_set))
  end

  test "should show word_search_set" do
    get :show, id: @word_search_set
    assert_response :success
  end

  test "should get edit" do
    get :edit, id: @word_search_set
    assert_response :success
  end

  test "should update word_search_set" do
    put :update, id: @word_search_set, word_search_set: {  }
    assert_redirected_to word_search_set_path(assigns(:word_search_set))
  end

  test "should destroy word_search_set" do
    assert_difference('WordSearchSet.count', -1) do
      delete :destroy, id: @word_search_set
    end

    assert_redirected_to word_search_sets_path
  end
end
