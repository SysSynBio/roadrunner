/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 *  Base class for extending SBML objects in packages.
 <p>
 * <p style='color: #777; font-style: italic'>
This class of objects is defined by libSBML only and has no direct
equivalent in terms of SBML components.  This class is not prescribed by
the SBML specifications, although it is used to implement features
defined in SBML.
</p>

 <p>
 * The {@link SBasePlugin} class is libSBML's base class for extensions of core SBML
 * component objects.  {@link SBasePlugin} defines basic virtual methods for
 * reading/writing/checking additional attributes and/or subobjects; these
 * methods should be overridden by subclasses to implement the necessary
 * features of an extended SBML object.
 <p>
 * Perhaps the easiest way to explain and motivate the role of {@link SBasePlugin} is
 * through an example.  The SBML Layout package specifies the existence of an
 * element, <code>&lt;listOfLayouts&gt;</code>, contained inside an SBML
 * <code>&lt;model&gt;</code> element.  In terms of libSBML components, this
 * means a new ListOfLayouts class of objects must be defined, and this
 * object placed in an <em>extended</em> class of {@link Model} (because {@link Model} in
 * plain/core SBML does not allow the inclusion of a ListOfLayouts
 * subobject).  This extended class of {@link Model} is LayoutModelPlugin, and it is
 * derived from {@link SBasePlugin}.
 <p>
 * <h2>How to extend {@link SBasePlugin} for a package implementation</h2>
 * <p>
 * LibSBML package extensions can extend existing libSBML objects such as {@link Model}
 * using {@link SBasePlugin} as a base class, to hold attributes and/or subcomponents
 * necessary for the SBML package being implemented.  Package developers must
 * implement an {@link SBasePlugin} extended class for each element to be extended
 * (e.g., {@link Model}, {@link Reaction}, and others) where additional attributes and/or
 * top-level objects of the package extension are directly contained.  The
 * following subsections detail the basic steps necessary to use {@link SBasePlugin}
 * for the implementation of a class extension.
 <p>
 * <h3>1. Identify the SBML components that need to be extended</h3>
 <p>
 * The specification for a SBML Level&nbsp;3 package will define the
 * attributes and subojects that make up the package constructs.  Those
 * constructs that modify existing SBML components such as {@link Model},
 * {@link Reaction}, etc., will be the ones that need to be extended using {@link SBasePlugin}.
 <p>
 * For example, the Layout package makes additions to {@link Model},
 * {@link SpeciesReference}, and the <code>&lt;sbml&gt;</code> element (which is
 * represented in libSBML by {@link SBMLDocument}).  This means that the Layout
 * package extension in libSBML needs to define extended versions of {@link Model},
 * {@link SpeciesReference} and {@link SBMLDocument}.  Elements <em>other</em> than the SBML
 * document need to be implemented using {@link SBasePlugin}; the document component
 * must be implemented using {@link SBMLDocumentPlugin} instead.
 <p>
 * <h3>2. Create a {@link SBasePlugin} subclass for each extended SBML component</h3>
 <p>
 * A new class definition that subclasses {@link SBasePlugin} needs to be created for
 * each SBML component to be extended by the package.  For instance, the
 * Layout package needs LayoutModelPlugin and LayoutSpeciesReferencePlugin.
 * (As mentioned above, the Layout class also needs LayoutSBMLDocumentPlugin,
 * but this one is implemented using {@link SBMLDocumentPlugin} instead of
 * {@link SBasePlugin}.)  Below, we describe in detail the different parts of an
 * {@link SBasePlugin} subclass definition.
 <p>
 * <h4>2.1 Define protected data members</h4>
 <p>
 * Data attributes on each extended class in an SBML package will have one of
 * the data types <code>String</code>, <code>double</code>,
 * <code>int</code>, or <code>boolean</code>.  Subelements/subobjects will normally
 * be derived from the {@link ListOf} class or from {@link SBase}.
 <p>
 * The additional data members must be properly initialized in the class
 * constructor, and must be properly copied in the copy constructor and
 * assignment operator.  For example, the following data member is defined in
 * the <code>GroupsModelPlugin</code> class (in the file
 * <code>GroupsModelPlugin.h</code>):
 * <pre class='fragment'>{.cpp}
ListOfGroups mGroups;
</pre>
 <p>
 * <h4>2.2 Override {@link SBasePlugin} class-related methods</h4>
 <p>
 * The derived class must override the constructor, copy constructor, assignment
 * operator (<code>operator=</code>) and <code>clone()</code> methods from
 * {@link SBasePlugin}.
 <p>
 * <h4>2.3 Override {@link SBasePlugin} virtual methods for attributes</h4>
 <p>
 * If the extended component is defined by the SBML Level&nbsp;3 package to have
 * attributes, then the extended class definition needs to override the
 * following internal methods on {@link SBasePlugin} and provide appropriate
 * implementations:
 <p>
 * <ul>
 * <li> <code>addExpectedAttributes(ExpectedAttributes& attributes)</code>: This
 * method should add the attributes that are expected to be found on this kind
 * of extended component in an SBML file or data stream.
 <p>
 * <li> <code>readAttributes(XMLAttributes attributes, ExpectedAttributes&
 * expectedAttributes)</code>: This method should read the attributes
 * expected to be found on this kind of extended component in an SBML file or
 * data stream.
 <p>
 * <li> <code>hasRequiredAttributes()</code>: This method should return <code>true</code>
 * if all of the required attribute for this extended component are present on
 * instance of the object.
 <p>
 * <li> <code>writeAttributes(XMLOutputStream stream)</code>: This method should
 * write out the attributes of an extended component.  The implementation should
 * use the different kinds of <code>writeAttribute</code> methods defined by
 * {@link XMLOutputStream} to achieve this.
 *
 * </ul> <p>
 * <h4>2.4 Override {@link SBasePlugin} virtual methods for subcomponents</h4>
 <p>
 * If the extended component is defined by the Level&nbsp;3 package to have
 * subcomponents (i.e., full XML elements rather than mere attributes), then the
 * extended class definition needs to override the following internal
 * {@link SBasePlugin} methods and provide appropriate implementations:
 <p>
 * <ul>
 * <li> <code>createObject(XMLInputStream stream)</code>: Subclasses must
 * override this method to create, store, and then return an SBML object
 * corresponding to the next {@link XMLToken} in the {@link XMLInputStream}.  To do this,
 * implementations can use methods like <code>peek()</code> on {@link XMLInputStream} to
 * test if the next object in the stream is something expected for the package.
 * For example, LayoutModelPlugin uses <code>peek()</code> to examine the next
 * element in the input stream, then tests that element against the Layout
 * namespace and the element name <code>'listOfLayouts'</code> to see if it's
 * the single subcomponent (ListOfLayouts) permitted on a {@link Model} object using the
 * Layout package.  If it is, it returns the appropriate object.
 <p>
 * <li> <code>connectToParent(SBase sbase)</code>: This creates a parent-child
 * relationship between a given extended component and its subcomponent(s).
 <p>
 * <li> <code>setSBMLDocument(SBMLDocument d)</code>: This method should set the
 * parent {@link SBMLDocument} object on the subcomponent object instances, so that the
 * subcomponent instances know which {@link SBMLDocument} contains them.
 <p>
 * <li> <code>enablePackageInternal(String& pkgURI, String& pkgPrefix,
 * boolean flag)</code>: This method should enable or disable the subcomponent
 * based on whether a given XML namespace is active.
 <p>
 * <li> <code>writeElements(XMLOutputStream stream)</code>: This method must be
 * overridden to provide an implementation that will write out the expected
 * subcomponents/subelements to the XML output stream.
 <p>
 * <li> <code>readOtherXML(SBase parentObject, {@link XMLInputStream} stream)</code>:
 * This function should be overridden if elements of annotation, notes, MathML
 * content, etc., need to be directly parsed from the given {@link XMLInputStream}
 * object.
 <p>
 * <li> <code>hasRequiredElements()</code>: This method should return <code>true</code> if
 * a given object contains all the required subcomponents defined by the
 * specification for that SBML Level&nbsp;3 package.
 *
 * </ul> <p>
 * <h4>2.5 Override {@link SBasePlugin} virtual methods for XML namespaces</h4>
 <p>
 * If the package needs to add additional <code>xmlns</code> attributes to
 * declare additional XML namespace URIs, the extended class should override the
 * following method:
 <p>
 * <ul>
 * <li> <code>writeXMLNS(XMLOutputStream stream)</code>: This method should
 * write out any additional XML namespaces that might be needed by a package
 * implementation.
 *
 * </ul> <p>
 * <h4>2.6 Implement additional methods as needed</h4>
 <p>
 * Extended component implementations can add whatever additional utility
 * methods are useful for their implementation.
 */

public class SBasePlugin {
   private long swigCPtr;
   protected boolean swigCMemOwn;

   protected SBasePlugin(long cPtr, boolean cMemoryOwn)
   {
     swigCMemOwn = cMemoryOwn;
     swigCPtr    = cPtr;
   }

   protected static long getCPtr(SBasePlugin obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (SBasePlugin obj)
   {
     long ptr = 0;

     if (obj != null)
     {
       ptr             = obj.swigCPtr;
       obj.swigCMemOwn = false;
     }

     return ptr;
   }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libsbmlJNI.delete_SBasePlugin(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  
/**
   * Returns the namespace URI of the package to which this plugin object
   * belongs.
   <p>
   * @return the XML namespace URI of the SBML Level&nbsp;3 package
   * implemented by this libSBML package extension.
   */ public
 String getElementNamespace() {
    return libsbmlJNI.SBasePlugin_getElementNamespace(swigCPtr, this);
  }

  
/**
   * Returns the XML namespace prefix of the package to which this plugin
   * object belongs.
   <p>
   * @return the XML namespace prefix of the SBML Level&nbsp;3 package
   * implemented by this libSBML package extension.
   */ public
 String getPrefix() {
    return libsbmlJNI.SBasePlugin_getPrefix(swigCPtr, this);
  }

  
/**
   * Returns the short-form name of the package to which this plugin
   * object belongs.
   <p>
   * @return the short-form package name (or nickname) of the SBML package
   * implemented by this package extension.
   */ public
 String getPackageName() {
    return libsbmlJNI.SBasePlugin_getPackageName(swigCPtr, this);
  }

  
/**
   * Creates and returns a deep copy of this {@link SBasePlugin} object.
   <p>
   * @return the (deep) copy of this {@link SBasePlugin} object.
   */ public
 SBasePlugin cloneObject() {
	return libsbml.DowncastSBasePlugin(libsbmlJNI.SBasePlugin_cloneObject(swigCPtr, this), true);
}

  
/**
   * Return the first child object found with a given identifier.
   <p>
   * This method searches all the subobjects under this one, compares their
   * identifiers to <code>id</code>, and returns the first one that machines.
   <p>
   * Normally, <code>SId</code> type identifier values are unique across
   * a model in SBML.  However, in some circumstances they may not be, such
   * as if a model is invalid because of multiple objects having the same
   * identifier.
   <p>
   * @param id string representing the identifier of the object to find
   <p>
   * @return pointer to the first object with the given <code>id</code>.
   */ public
 SBase getElementBySId(String id) {
  return libsbml.DowncastSBase(libsbmlJNI.SBasePlugin_getElementBySId(swigCPtr, this, id), false);
}

  
/**
   * Return the first child object found with a given meta identifier.
   <p>
   * This method searches all the subobjects under this one, compares their
   * meta identifiers to <code>metaid</code>, and returns the first one that machines.
   <p>
   * @param metaid string, the metaid of the object to find.
   <p>
   * @return pointer to the first object found with the given <code>metaid</code>.
   */ public
 SBase getElementByMetaId(String metaid) {
  return libsbml.DowncastSBase(libsbmlJNI.SBasePlugin_getElementByMetaId(swigCPtr, this, metaid), false);
}

  
/** * @internal */ public
 void connectToParent(SBase sbase) {
    libsbmlJNI.SBasePlugin_connectToParent(swigCPtr, this, SBase.getCPtr(sbase), sbase);
  }

  
/** * @internal */ public
 void enablePackageInternal(String pkgURI, String pkgPrefix, boolean flag) {
    libsbmlJNI.SBasePlugin_enablePackageInternal(swigCPtr, this, pkgURI, pkgPrefix, flag);
  }

  
/** * @internal */ public
 boolean stripPackage(String pkgPrefix, boolean flag) {
    return libsbmlJNI.SBasePlugin_stripPackage(swigCPtr, this, pkgPrefix, flag);
  }

  
/**
   * Returns the {@link SBMLDocument} object containing this object instance.
   <p>
   * <p>
 * LibSBML uses the class {@link SBMLDocument} as a top-level container for
 * storing SBML content and data associated with it (such as warnings and
 * error messages).  An SBML model in libSBML is contained inside an
 * {@link SBMLDocument} object.  {@link SBMLDocument} corresponds roughly to the class
 * <i>SBML</i> defined in the SBML Level&nbsp;3 and Level&nbsp;2
 * specifications, but it does not have a direct correspondence in SBML
 * Level&nbsp;1.  (But, it is created by libSBML no matter whether the
 * model is Level&nbsp;1, Level&nbsp;2 or Level&nbsp;3.)
   <p>
   * This method allows the caller to obtain the {@link SBMLDocument} for the
   * current object.
   <p>
   * @return the parent {@link SBMLDocument} object of this plugin object.
   <p>
   * @see #getParentSBMLObject()
   */ public
 SBMLDocument getSBMLDocument() {
    long cPtr = libsbmlJNI.SBasePlugin_getSBMLDocument__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new SBMLDocument(cPtr, false);
  }

  
/**
   * Returns the XML namespace URI for the package to which this object belongs.
   <p>
   * <p>
 * In the XML representation of an SBML document, XML namespaces are used to
 * identify the origin of each XML construct used.  XML namespaces are
 * identified by their unique resource identifiers (URIs).  The core SBML
 * specifications stipulate the namespaces that must be used for core SBML
 * constructs; for example, all XML elements that belong to SBML Level&nbsp;3
 * Version&nbsp;1 Core must be placed in the XML namespace identified by the URI
 * <code>'http://www.sbml.org/sbml/level3/version1/core'</code>.  Individual
 * SBML Level&nbsp;3 packages define their own XML namespaces; for example,
 * all elements belonging to the SBML Level&nbsp;3 Layout Version&nbsp;1
 * package must be placed in the XML namespace
 * <code>'http://www.sbml.org/sbml/level3/version1/layout/version1/'</code>.
   <p>
   * This method first looks into the {@link SBMLNamespaces} object possessed by the
   * parent {@link SBMLDocument} object of the current object.  If this cannot be
   * found, this method returns the result of getElementNamespace().
   <p>
   * @return a string, the URI of the XML namespace to which this object belongs.
   <p>
   * @see #getPackageName()
   * @see #getElementNamespace()
   * @see SBMLDocument#getSBMLNamespaces()
   * @see #getSBMLDocument()
   */ public
 String getURI() {
    return libsbmlJNI.SBasePlugin_getURI(swigCPtr, this);
  }

  
/**
   * Returns the parent object to which this plugin object is connected.
   <p>
   * @return the parent object of this object.
   */ public
 SBase getParentSBMLObject() {
  return libsbml.DowncastSBase(libsbmlJNI.SBasePlugin_getParentSBMLObject__SWIG_0(swigCPtr, this), false);
}

  
/**
   * Sets the XML namespace to which this object belongs.
   <p>
   * <p>
 * In the XML representation of an SBML document, XML namespaces are used to
 * identify the origin of each XML construct used.  XML namespaces are
 * identified by their unique resource identifiers (URIs).  The core SBML
 * specifications stipulate the namespaces that must be used for core SBML
 * constructs; for example, all XML elements that belong to SBML Level&nbsp;3
 * Version&nbsp;1 Core must be placed in the XML namespace identified by the URI
 * <code>'http://www.sbml.org/sbml/level3/version1/core'</code>.  Individual
 * SBML Level&nbsp;3 packages define their own XML namespaces; for example,
 * all elements belonging to the SBML Level&nbsp;3 Layout Version&nbsp;1
 * package must be placed in the XML namespace
 * <code>'http://www.sbml.org/sbml/level3/version1/layout/version1/'</code>.
   <p>
   * @param uri the URI to assign to this object.
   <p>
   * <p>
 * @return integer value indicating success/failure of the
 * function.   The possible values
 * returned by this function are:
   * <ul>
   * <li> {@link libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS}
   *
   * </ul> <p>
   * @see #getElementNamespace()
   */ public
 int setElementNamespace(String uri) {
    return libsbmlJNI.SBasePlugin_setElementNamespace(swigCPtr, this, uri);
  }

  
/**
   * Returns the SBML Level of the package extension of this plugin object.
   <p>
   * @return the SBML Level.
   <p>
   * @see #getVersion()
   */ public
 long getLevel() {
    return libsbmlJNI.SBasePlugin_getLevel(swigCPtr, this);
  }

  
/**
   * Returns the Version within the SBML Level of the package extension of
   * this plugin object.
   <p>
   * @return the SBML Version.
   <p>
   * @see #getLevel()
   */ public
 long getVersion() {
    return libsbmlJNI.SBasePlugin_getVersion(swigCPtr, this);
  }

  
/**
   * Returns the package version of the package extension of this plugin
   * object.
   <p>
   * @return the package version of the package extension of this plugin
   * object.
   <p>
   * @see #getLevel()
   * @see #getVersion()
   */ public
 long getPackageVersion() {
    return libsbmlJNI.SBasePlugin_getPackageVersion(swigCPtr, this);
  }

  
/** * @internal */ public
 void replaceSIDWithFunction(String id, ASTNode function) {
    libsbmlJNI.SBasePlugin_replaceSIDWithFunction(swigCPtr, this, id, ASTNode.getCPtr(function), function);
  }

  
/** * @internal */ public
 void divideAssignmentsToSIdByFunction(String id, ASTNode function) {
    libsbmlJNI.SBasePlugin_divideAssignmentsToSIdByFunction(swigCPtr, this, id, ASTNode.getCPtr(function), function);
  }

  
/** * @internal */ public
 void multiplyAssignmentsToSIdByFunction(String id, ASTNode function) {
    libsbmlJNI.SBasePlugin_multiplyAssignmentsToSIdByFunction(swigCPtr, this, id, ASTNode.getCPtr(function), function);
  }

  
/** * @internal */ public
 boolean hasIdentifierBeginningWith(String prefix) {
    return libsbmlJNI.SBasePlugin_hasIdentifierBeginningWith(swigCPtr, this, prefix);
  }

  
/** * @internal */ public
 int prependStringToAllIdentifiers(String prefix) {
    return libsbmlJNI.SBasePlugin_prependStringToAllIdentifiers(swigCPtr, this, prefix);
  }

  
/** * @internal */ public
 int transformIdentifiers(IdentifierTransformer sidTransformer) {
    return libsbmlJNI.SBasePlugin_transformIdentifiers(swigCPtr, this, IdentifierTransformer.getCPtr(sidTransformer), sidTransformer);
  }

  
/** * @internal */ public
 long getLine() {
    return libsbmlJNI.SBasePlugin_getLine(swigCPtr, this);
  }

  
/** * @internal */ public
 long getColumn() {
    return libsbmlJNI.SBasePlugin_getColumn(swigCPtr, this);
  }

  
/** * @internal */ public
 SBMLNamespaces getSBMLNamespaces() {
  return libsbml.DowncastSBMLNamespaces(libsbmlJNI.SBasePlugin_getSBMLNamespaces(swigCPtr, this), false);
}

  
/** * @internal */ public
 void logUnknownElement(String element, long sbmlLevel, long sbmlVersion, long pkgVersion) {
    libsbmlJNI.SBasePlugin_logUnknownElement(swigCPtr, this, element, sbmlLevel, sbmlVersion, pkgVersion);
  }

  
  /**
   * Returns an {@link SBaseList} of all child {@link SBase} objects,
   * including those nested to an arbitrary depth.
   *
   * @return a pointer to an {@link SBaseList} of pointers to all children objects.
   */
 public SBaseList getListOfAllElements(ElementFilter filter) {
    long cPtr = libsbmlJNI.SBasePlugin_getListOfAllElements__SWIG_0(swigCPtr, this, ElementFilter.getCPtr(filter), filter);
    return (cPtr == 0) ? null : new SBaseList(cPtr, false);
  }

  
  /**
   * Returns an {@link SBaseList} of all child {@link SBase} objects,
   * including those nested to an arbitrary depth.
   *
   * @return a pointer to an {@link SBaseList} of pointers to all children objects.
   */
 public SBaseList getListOfAllElements() {
    long cPtr = libsbmlJNI.SBasePlugin_getListOfAllElements__SWIG_1(swigCPtr, this);
    return (cPtr == 0) ? null : new SBaseList(cPtr, false);
  }

}