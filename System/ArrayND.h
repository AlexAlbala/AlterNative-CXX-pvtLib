#pragma once
#include <System/Collections/Generic/IteratorCXX.h>
#include <boost/multi_array.hpp>
#include <iostream>

using namespace System::Collections::Generic;
namespace System{
	namespace __Internal__ {
		template<typename T, int dimensions>
		class ArrayND_T_Base : public Object{

		private:
			typedef boost::multi_array<TypeDecl(T), dimensions> array_type;
			typedef typename array_type::index index;
			array_type narray;

		public:
			ArrayND_T_Base(){
			}

			ArrayND_T_Base(int d1, int d2){				
				narray = CREATE_MD_ARRAY(narray, d1, d2);
			}

			ArrayND_T_Base(int d1, int d2, int d3){				
				narray = CREATE_MD_ARRAY(narray, d1, d2, d3);
			}

			ArrayND_T_Base(int d1, int d2, int d3, int d4){				
				narray = CREATE_MD_ARRAY(narray, d1, d2, d3, d4);
			}

			ArrayND_T_Base(int d1, int d2, int d3, int d4, int d5){				
				narray = CREATE_MD_ARRAY(narray, d1, d2, d3, d4, d5);
			}
			
			TypeDecl(T) GetData(int d1, int d2)
			{
				return (TypeDecl(T))narray[d1][d2];
				//return (TypeDecl(T))GET_MD_ARRAY(narray, d1, d2);
			}

			TypeDecl(T) GetData(int d1, int d2, int d3)
			{
				return (TypeDecl(T))narray[d1][d2][d3];
			}

			TypeDecl(T) GetData(int d1, int d2, int d3, int d4)
			{
				return (TypeDecl(T))narray[d1][d2][d3][d4];
			}

			TypeDecl(T) GetData(int d1, int d2, int d3, int d4, int d5)
			{
				return (TypeDecl(T))narray[d1][d2][d3][d4][d5];
			}


			void SetData(TypeDecl(T) value, int d1, int d2)
			{
				narray[d1][d2] = value;
				//SET_MD_ARRAY(narray, value, d1, d2);
			}

			void SetData(TypeDecl(T) value, int d1, int d2, int d3)
			{
				narray[d1][d2][d3] = value;
			}

			void SetData(TypeDecl(T) value, int d1, int d2, int d3, int d4)
			{
				narray[d1][d2][d3][d4] = value;
			}

			void SetData(TypeDecl(T) value, int d1, int d2, int d3, int d4, int d5)
			{
				narray[d1][d2][d3][d4][d5]= value;
			}

			iteratorcxx<TypeArg(T)>* begin()
			{
				return narray.begin();
			}

			iteratorcxx<TypeArg(T)>* begin() const
			{
				return narray.begin();
			}

			iteratorcxx<TypeArg(T)>* end()
			{			
				return narray.end();
			}

			iteratorcxx<TypeArg(T)>* end() const
			{
				return narray.end();
			}

			iteratorcxx<TypeArg(T)>* rbegin()
			{			
				return narray.rbegin();
			}

			iteratorcxx<TypeArg(T)>* rbegin() const
			{
				return narray.rbegin();
			}

			iteratorcxx<TypeArg(T)>* rend()
			{			
				return narray.rend();
			}

			iteratorcxx<TypeArg(T)>* rend() const
			{
				return narray.rend();
			}
		};


		template< typename T, bool, int dimensions>
		class ArrayND{
		};

		template<typename T, int dimensions>
		class ArrayND<T, true, dimensions> : public ArrayND_T_Base<T, dimensions>{
		public:
			ArrayND() : ArrayND_T_Base<T, dimensions>(){}

			template<typename ... Params>
			ArrayND(Params... args) : ArrayND_T_Base<T, dimensions>(args...){}
		};

		template<typename T, int dimensions>
		class ArrayND<T, false, dimensions> : public ArrayND_T_Base<Object*, dimensions>{
		public:
			inline ArrayND() : ArrayND_T_Base<Object*, dimensions>(){}

			template<typename ... Params>
			inline ArrayND(Params...  args) : ArrayND_T_Base<Object*, dimensions>(args...){}
			
			inline void SetData(T* element, ...){
				va_list arguments;
				ArrayND_T_Base<Object*, dimensions>::SetData((Object*)element, arguments);
			}

			inline T* GetData(...){
				va_list arguments;
				return reinterpret_cast<T*>(ArrayND_T_Base<Object*, dimensions>:GetData(arguments));//CUIDADO EL CAST
			}
		};
	}

	template<typename T, int dimensions>
	class ArrayND : public __Internal__::ArrayND<T, IsValueType(T), dimensions>{
	public:
		ArrayND() : __Internal__::ArrayND<T, IsValueType(T), dimensions>(){}

		template<typename ... Params>
		ArrayND(Params... args) : __Internal__::ArrayND<T, IsValueType(T), dimensions>(args...){}
	};
}
